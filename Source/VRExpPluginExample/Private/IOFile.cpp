// Fill out your copyright notice in the Description page of Project Settings.


#include "IOFile.h"
#include "../GalleryActor.h"
#include "../GalleryModel.h"
#include <Kismet/GameplayStatics.h>
#include <IDesktopPlatform.h>
#include "DesktopPlatformModule.h"
#include "DesktopPlatform/Public/DesktopPlatformModule.h"
#include "../PropManipulator.h"
#include "../ArtWorkLoader.h"
#include "../GalleryLight.h"
#include "../GalleryLabel.h"

// Sets default values
AIOFile::AIOFile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIOFile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIOFile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString OpenFileDialog(const FString FileTypes, const FString DialogTitle)
{
	// Ensure the platform module is available
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform)
	{

		// Variable to hold the selected file path
		TArray<FString> SelectedFile;

		// Open the file dialog
		bool bOpened = DesktopPlatform->OpenFileDialog(
			nullptr,                            // Parent window handle (null means no parent)
			DialogTitle,          // Dialog title
			TEXT(""),                           // Initial directory (empty means default directory)
			TEXT(""),                           // Default file name (optional)
			TEXT(""),                          // Filter for allowed file types
			EFileDialogFlags::None,             // Flags (use None unless you want additional behavior)
			SelectedFile                        // The path of the selected file
		);

		// Return the file path if a file was selected, else return empty
		if (bOpened && !SelectedFile.IsEmpty() && !SelectedFile[0].IsEmpty())
		{
			return SelectedFile[0];
		}
	}

	return FString(); // Return an empty string if no file was selected
}

FRoom AIOFile::LoadRoom(bool IsVr) {
	FString FilePath = !IsVr ? OpenFileDialog("", "") : FPaths::ProjectDir() + "default.txt";

	if (FilePath.IsEmpty()) {
		return FRoom(20, 5, 15, "");
	}

	FString FileContent;

	if (FFileHelper::LoadFileToString(FileContent, *FilePath))
	{
		TArray<FString> Lines;
		FileContent.ParseIntoArray(Lines, TEXT("\n"), true);

		TArray<FString> ParsedValues;
		Lines.Last().ParseIntoArray(ParsedValues, TEXT(" "), true);

		float Width = FCString::Atof(*ParsedValues[0]);
		float Height = FCString::Atof(*ParsedValues[1]);
		float Length = FCString::Atof(*ParsedValues[2]);

		return FRoom(Width, Height, Length, FilePath);
	}

	return FRoom(10, 5, 12, "");
}

void AIOFile::LoadActors(FString FileName) {
	if (FileName.IsEmpty()) {
		return;
	}

	UClass* InventorySystemClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/VRArtGallery/Inventory/InventorySystem.InventorySystem_C"));
	AActor* InventorySystem = UGameplayStatics::GetActorOfClass(GetWorld(), InventorySystemClass);
	if (!InventorySystem) {
		UE_LOG(LogTemp, Error, TEXT("Failed to load InventorySystem Blueprint class."));
		return;
	};

	FProperty* Property = InventorySystem->GetClass()->FindPropertyByName("Currently Selected");
	FIntProperty* IntProperty = CastField<FIntProperty>(Property);

	UFunction* Function = InventorySystem->FindFunction(FName("Spawn Actor"));

	FString FileContent;

	if (FFileHelper::LoadFileToString(FileContent, *FileName))
	{
		TArray<FString> Lines;
		FileContent.ParseIntoArray(Lines, TEXT("\n"), true);

		int lastTexture = 0;

		for (int i = 0; i < Lines.Num() - 1 && !Lines[i].Equals("###"); i++) {
			UTexture2D* tex = LoadTextureFromFile(Lines[i]);
			CreateArtPiece(tex, Lines[i]);
			FileFiles.Add(Lines[i]);
			lastTexture = i;
		}

		int lastIntensivity = lastTexture + 1;

		TArray<float> intensivities;
		for (int i = lastTexture + 2; i < Lines.Num() - 1 && !Lines[i].Equals("###"); i++) {
			intensivities.Add(FCString::Atof(*Lines[i]));
			lastIntensivity = i;
		}

		TArray<FString> labels;
		FString currentLabel = "";
		for (int i = lastIntensivity + 2; i < Lines.Num() - 1; i++) {
			if (Lines[i].Equals("#")) {
				labels.Add(currentLabel);
				currentLabel = "";
			}
			else {
				currentLabel += "\n";
				currentLabel += Lines[i];
			}
		}
		labels.Add(currentLabel);

		TArray<FString> ParsedValues;
		Lines.Last().ParseIntoArray(ParsedValues, TEXT(" "), true);

		for (int i = 4; i < ParsedValues.Num() - 10; i += 12) 
		{
			int type = FCString::Atoi(*ParsedValues[i]);
			float x = FCString::Atof(*ParsedValues[i + 1]);
			float y = FCString::Atof(*ParsedValues[i + 2]);
			float z = FCString::Atof(*ParsedValues[i + 3]);
			float rx = FCString::Atof(*ParsedValues[i + 4]);
			float ry = FCString::Atof(*ParsedValues[i + 5]);
			float rz = FCString::Atof(*ParsedValues[i + 6]);
			float rw = FCString::Atof(*ParsedValues[i + 7]);
			float sx = FCString::Atof(*ParsedValues[i + 8]);
			float sy = FCString::Atof(*ParsedValues[i + 9]);
			float sz = FCString::Atof(*ParsedValues[i + 10]);

			IntProperty->SetPropertyValue_InContainer(InventorySystem, type);

			struct FSpawnActorParams
			{
				FTransform Transform;
				AGalleryActor* SpawnedActor;
			} Parameters;
			Parameters.Transform = FTransform(FRotator(FQuat(rx, ry, rz, rw)), FVector(x, y, z), FVector(sx, sy, sz));
			Parameters.SpawnedActor = nullptr;
			InventorySystem->ProcessEvent(Function, &Parameters);
			AGalleryActor* SpawnedActor = Parameters.SpawnedActor;

			FileTypes.Add(type);
			FilePositions.Add(FVector(x, y, z));
			FileRotations.Add(FQuat(rx, ry, rz, rw));
			FileScales.Add(FVector(sx, sy, sz));
		}

		TArray<AActor*> FoundLights;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGalleryLight::StaticClass(), FoundLights);

		for (int i = 0; i < FoundLights.Num() && i < intensivities.Num(); i++) {
			AGalleryLight* Light = Cast<AGalleryLight>(FoundLights[i]);
			Light->UpdateIntensity(intensivities[i]);
		}

		TArray<AActor*> FoundLabels;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGalleryLabel::StaticClass(), FoundLabels);

		for (int i = 0; i < FoundLabels.Num() && i < labels.Num(); i++) {
			AGalleryLabel* Label = Cast<AGalleryLabel>(FoundLabels[i]);
			Label->UpdateText(labels[i]);
		}
	}
}

UTexture2D* AIOFile::LoadTextureFromFile(const FString& FilePath)
{
	// Try to load the texture using the ImageUtils helper function
	UTexture2D* Texture = FImageUtils::ImportFileAsTexture2D(FilePath);
	return Texture;
}

void AIOFile::CreateArtPiece(UTexture2D* ArtTexture, const FString& name) {
	if (ArtTexture)
	{
		UWorld* World = GetWorld();
		FVector SpawnLocation = FVector(0, 0, 400);

		// Get the current world
		if (World)
		{
			// Set up spawn parameters
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			// Create a dynamic material instance from the current material
			UMaterial* BaseMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Script/Engine.Material'/Game/VRArtGallery/ArtPieceMaterial.ArtPieceMaterial'"));
			UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);

			// Set the texture parameter dynamically
			DynamicMaterial->SetTextureParameterValue(FName("ArtTexture"), ArtTexture);

			UArtWorkData* ArtworkData = NewObject<UArtWorkData>();
			ArtworkData->Name = FPaths::GetBaseFilename(name);
			ArtworkData->Width = ArtTexture->GetSizeX();
			ArtworkData->Height = ArtTexture->GetSizeY();
			ArtworkData->ArtWorkMaterial = DynamicMaterial;

			UClass* InventorySystemClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/VRArtGallery/Inventory/InventorySystem.InventorySystem_C"));
			AActor* InventorySystem = UGameplayStatics::GetActorOfClass(GetWorld(), InventorySystemClass);
			if (!InventorySystem) {
				UE_LOG(LogTemp, Error, TEXT("Failed to load InventorySystem Blueprint class."));
				return;
			};
			UFunction* Function = InventorySystem->FindFunction(FName("Add Item To Inventory"));
			struct { UArtWorkData* ArtworkData; } Parameters;
			Parameters.ArtworkData = ArtworkData;
			InventorySystem->ProcessEvent(Function, &Parameters);

		}
	}
}

void AIOFile::SaveScene() {
	auto FilePath = OpenFileDialog("", "");

	if (FilePath.IsEmpty()) {
		return;
	}

	FString ResultString = "";

	TArray<AActor*> FoundActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArtworkLoader::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		AArtworkLoader* ArtworkLoader = Cast<AArtworkLoader>(FoundActors[0]);
		if (ArtworkLoader)
		{
			auto Files = ArtworkLoader->Files;

			for (int32 i = 0; i < Files.Num(); i++)
			{
				ResultString += Files[i] + "\n";
			}
			for (int32 i = 0; i < FileFiles.Num(); i++)
			{
				ResultString += FileFiles[i] + "\n";
			}
		}
		else {
			ResultString = "actor cannot be cast";
			FFileHelper::SaveStringToFile(ResultString, *FilePath);
			return;
		}
	}
	else {
		ResultString = "actor not found";
		FFileHelper::SaveStringToFile(ResultString, *FilePath);
		return;
	}

	ResultString += "###\n";

	TArray<AActor*> FoundLights;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGalleryLight::StaticClass(), FoundLights);
	for (int i = 0; i < FoundLights.Num(); i++) {
		AGalleryLight* Light = Cast<AGalleryLight>(FoundLights[i]);
		ResultString += FString::Printf(TEXT("%f\n"), Light->GetIntensity());
	}

	ResultString += "###\n";

	TArray<AActor*> FoundLabels;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGalleryLabel::StaticClass(), FoundLabels);
	for (int i = 0; i < FoundLabels.Num(); i++) {
		AGalleryLabel* Label = Cast<AGalleryLabel>(FoundLabels[i]);
		ResultString += Label->GetText();
		ResultString += "\n#\n";
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APropManipulator::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		APropManipulator* PropManipulator = Cast<APropManipulator>(FoundActors[0]);
		if (PropManipulator)
		{
			UClass* InventorySystemClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/VRArtGallery/BP_Room.BP_Room_C"));

			if (!InventorySystemClass) {
				FFileHelper::SaveStringToFile(TEXT("Bluprint cannot be found"), *FilePath);
				return;
			};

			AActor* InventorySystem = UGameplayStatics::GetActorOfClass(GetWorld(), InventorySystemClass);
			if (!InventorySystem) {
				FFileHelper::SaveStringToFile(TEXT("Bluprint cannot be load"), *FilePath);
				return;
			};

			for (TFieldIterator<FProperty> It(InventorySystem->GetClass()); It; ++It)
			{
				if (FProperty* Prop = *It)
				{
					// Get the property name
					const FString PropName = Prop->GetName();
					// Get the property�s C++ type
					const FString PropType = Prop->GetCPPType();

					UE_LOG(LogTemp, Warning, TEXT("Property found: %s (type = %s)"), *PropName, *PropType);
				}
			}

			FProperty* WidthProperty = InventorySystem->GetClass()->FindPropertyByName("Width");

			if (!WidthProperty) {
				FFileHelper::SaveStringToFile(TEXT("Property cannot be load"), *FilePath);
				return;
			}

			FDoubleProperty* IntWidthProperty = CastField<FDoubleProperty>(WidthProperty);

			if (!IntWidthProperty) {
				FFileHelper::SaveStringToFile(TEXT("Property cannot be cast"), *FilePath);
				return;
			}

			float Width = IntWidthProperty->GetPropertyValue_InContainer(InventorySystem);

			FProperty* HeightProperty = InventorySystem->GetClass()->FindPropertyByName("Height");
			FDoubleProperty* IntHeightProperty = CastField<FDoubleProperty>(HeightProperty);
			float Height = IntHeightProperty->GetPropertyValue_InContainer(InventorySystem);

			FProperty* LengthProperty = InventorySystem->GetClass()->FindPropertyByName("Length");
			FDoubleProperty* IntLengthProperty = CastField<FDoubleProperty>(LengthProperty);
			float Length = IntLengthProperty->GetPropertyValue_InContainer(InventorySystem);

			auto Positions = PropManipulator->Positions;
			auto Rotations = PropManipulator->Rotations;
			auto Scales = PropManipulator->Scales;
			auto Types = PropManipulator->Types;
			ResultString += FString::Printf(TEXT("%f %f %f | "), Width, Height, Length);

			for (int32 i = 0; i < Positions.Num(); i++)
			{
				ResultString += FString::Printf(TEXT("%d %f %f %f %f %f %f %f %f %f %f"), Types[i], Positions[i].X, Positions[i].Y, Positions[i].Z, Rotations[i].X, Rotations[i].Y, Rotations[i].Z, Rotations[i].W, Scales[i].X, Scales[i].Y, Scales[i].Z);

				// Add a space between numbers, but avoid a trailing space
				if (i < Positions.Num() - 1 || FilePositions.Num() > 0)
				{
					ResultString += TEXT(" | ");
				}
			}

			for (int32 i = 0; i < FilePositions.Num(); i++)
			{
				ResultString += FString::Printf(TEXT("%d %f %f %f %f %f %f %f %f %f %f"), FileTypes[i], FilePositions[i].X, FilePositions[i].Y, FilePositions[i].Z, FileRotations[i].X, FileRotations[i].Y, FileRotations[i].Z, FileRotations[i].W, FileScales[i].X, FileScales[i].Y, FileScales[i].Z);

				// Add a space between numbers, but avoid a trailing space
				if (i < FilePositions.Num() - 1)
				{
					ResultString += TEXT(" | ");
				}
			}


			FFileHelper::SaveStringToFile(ResultString, *FilePath);
		}
		else {
			ResultString = "actor cannot be cast";
			FFileHelper::SaveStringToFile(ResultString, *FilePath);
		}
	}
	else {
		ResultString = "actor not found";
		FFileHelper::SaveStringToFile(ResultString, *FilePath);
	}
}
