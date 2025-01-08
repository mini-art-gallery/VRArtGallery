// Fill out your copyright notice in the Description page of Project Settings.


#include "PropManipulator.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "ArtPiece.h"

// Sets default values
APropManipulator::APropManipulator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APropManipulator::ScaleObject(float scale)
{
	// Get Inventory System.
	UClass* InventorySystemClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/VRArtGallery/Inventory/InventorySystem.InventorySystem_C"));
	AActor* InventorySystem = UGameplayStatics::GetActorOfClass(GetWorld(), InventorySystemClass);
	if (!InventorySystem) {
		UE_LOG(LogTemp, Error, TEXT("Failed to load InventorySystem Blueprint class."));
		return;
	};

	// Get the raycasted actor for transform.
	FProperty* Property = InventorySystem->GetClass()->FindPropertyByName("Selected Actor");
	FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property);
	AGalleryActor* SelectedActor = Cast<AGalleryActor>(ObjectProperty->GetObjectPropertyValue_InContainer(InventorySystem));

	auto actorScale = SelectedActor->GetActorRelativeScale3D();
	actorScale *= scale;
	SelectedActor->SetActorRelativeScale3D(actorScale);
}

void APropManipulator::RotateObject(float degree)
{
	//// Get Inventory System.
	//UClass* InventorySystemClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/VRArtGallery/Inventory/InventorySystem.InventorySystem_C"));
	//AActor* InventorySystem = UGameplayStatics::GetActorOfClass(GetWorld(), InventorySystemClass);
	//if (!InventorySystem) {
	//	UE_LOG(LogTemp, Error, TEXT("Failed to load InventorySystem Blueprint class."));
	//	return;
	//};

	//// Get the raycasted actor for transform.
	//FProperty* Property = InventorySystem->GetClass()->FindPropertyByName("Selected Actor");
	//FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property);
	//AGalleryActor* SelectedActor = Cast<AGalleryActor>(ObjectProperty->GetObjectPropertyValue_InContainer(InventorySystem));

	//FRotator CurrentRotation = SelectedActor->GetActorRotation();
	//FRotator RotationOffset(0, degree, 0);
	//SelectedActor->SetActorRotation(CurrentRotation + RotationOffset);
	propRotation += degree;
}

// Called when the game starts or when spawned
void APropManipulator::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APropManipulator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TraceRay();
}

void APropManipulator::TraceRay()
{
	UClass* InventorySystemClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/VRArtGallery/Inventory/InventorySystem.InventorySystem_C"));
	AActor* InventorySystem = UGameplayStatics::GetActorOfClass(GetWorld(), InventorySystemClass);
	if (!InventorySystem) {
		UE_LOG(LogTemp, Error, TEXT("Failed to load InventorySystem Blueprint class."));
		return;
	};
	FProperty* IndexProperty = InventorySystem->GetClass()->FindPropertyByName("Currently Selected");
	int32* SelectedIndex = IndexProperty->ContainerPtrToValuePtr<int32>(InventorySystem);
	if (*SelectedIndex < 0) return;

	FProperty* Property = InventorySystem->GetClass()->FindPropertyByName("Selected Actor");
	FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property);
	AActor* ArtPiece = Cast<AActor>(ObjectProperty->GetObjectPropertyValue_InContainer(InventorySystem));

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APawn* Player = PlayerController ? PlayerController->GetPawn() : nullptr;

	if (!ArtPiece)
		return;


	UCameraComponent* CameraComponent = Player->FindComponentByClass<UCameraComponent>();

	// Get the Camera's location and rotation
	FVector CameraLocation = CameraComponent->GetComponentLocation();
	FRotator CameraRotation = CameraComponent->GetComponentRotation();

	// Get the player's camera location and forward vector (direction of the ray)
	FVector StartLocation = CameraLocation;
	FVector ForwardVector = CameraRotation.Vector();

	// Define the end of the ray (for example, 1000 units away)
	FVector EndLocation = StartLocation + (ForwardVector * 1000.0f);

	// Perform the line trace (raycast)
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Player);
	CollisionParams.AddIgnoredActor(ArtPiece);
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams);
	if (bHit) {
		ArtPiece->SetActorLocation(HitResult.Location, false);

		FRotator RotationOffset(-90, 0, 0);
		FRotator RotationOffsetFromUser(0, propRotation, 0);
		FQuat UserRotation = FQuat(HitResult.ImpactNormal, FMath::DegreesToRadians(propRotation));

		FRotator DesiredRotation = HitResult.ImpactNormal.Rotation() + RotationOffset;// +UserRotation.Rotator();
		ArtPiece->SetActorRotation(DesiredRotation);
		ArtPiece->AddActorLocalRotation(RotationOffsetFromUser);
	}
}

void APropManipulator::PlaceActiveProp() {
	// Get Inventory System.
	UClass* InventorySystemClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/VRArtGallery/Inventory/InventorySystem.InventorySystem_C"));	
	AActor* InventorySystem = UGameplayStatics::GetActorOfClass(GetWorld(), InventorySystemClass);
	if (!InventorySystem) {
		UE_LOG(LogTemp, Error, TEXT("Failed to load InventorySystem Blueprint class."));
		return;
	};

	// Get the raycasted actor for transform.
	FProperty* Property = InventorySystem->GetClass()->FindPropertyByName("Selected Actor");
	FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property);
	AGalleryActor* SelectedActor = Cast<AGalleryActor>(ObjectProperty->GetObjectPropertyValue_InContainer(InventorySystem));

	UFunction* Function = InventorySystem->FindFunction(FName("Spawn Actor"));
	struct FSpawnActorParams
	{
		FTransform Transform;
		AGalleryActor* SpawnedActor;
	} Parameters;
	Parameters.Transform = SelectedActor->GetActorTransform();
	Parameters.SpawnedActor = nullptr;
	InventorySystem->ProcessEvent(Function, &Parameters);
	AGalleryActor* SpawnedActor = Parameters.SpawnedActor;
}

AGalleryActor* APropManipulator::GetLookedAtActor()
{

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APawn* Player = PlayerController ? PlayerController->GetPawn() : nullptr;

	UCameraComponent* CameraComponent = Player->FindComponentByClass<UCameraComponent>();

	// Get the Camera's location and rotation
	FVector CameraLocation = CameraComponent->GetComponentLocation();
	FRotator CameraRotation = CameraComponent->GetComponentRotation();

	// Get the player's camera location and forward vector (direction of the ray)
	FVector StartLocation = CameraLocation;
	FVector ForwardVector = CameraRotation.Vector();

	// Define the end of the ray (for example, 1000 units away)
	FVector EndLocation = StartLocation + (ForwardVector * 1000.0f);

	// Perform the line trace (raycast)
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Player);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams);
	if (bHit) {
		AActor* hitActor = HitResult.GetActor();
		// Return not nullptr if actor is an AGalleryActor.
		return Cast<AGalleryActor>(hitActor); 
	}
	return nullptr;
}
