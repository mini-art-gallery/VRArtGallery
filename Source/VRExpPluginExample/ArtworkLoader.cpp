// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtworkLoader.h"

#include "Engine/DirectionalLight.h"

void AArtworkLoader::LoadArtwork() {
    FString path = OpenFileDialog(TEXT("PNG Files|.png|JPEG Files|.jpg|All Files|."), TEXT("Select a PNG file"));
    UTexture2D* tex = LoadTextureFromFile(path);
    CreateArtPiece(tex, path);
    Files.Add(path);
}

void AArtworkLoader::BeginPlay()
{
    Super::BeginPlay();
}

FString AArtworkLoader::OpenFileDialog(const FString FileTypes, const FString DialogTitle)
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

UTexture2D* AArtworkLoader::LoadTextureFromFile(const FString& FilePath)
{
    // Try to load the texture using the ImageUtils helper function
    UTexture2D* Texture = FImageUtils::ImportFileAsTexture2D(FilePath);
    return Texture;
}


void AArtworkLoader::CreateArtPiece(UTexture2D* ArtTexture, const FString& name) {
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
