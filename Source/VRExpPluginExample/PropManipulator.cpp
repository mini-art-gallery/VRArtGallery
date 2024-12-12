// Fill out your copyright notice in the Description page of Project Settings.


#include "PropManipulator.h"
#include "Kismet/GameplayStatics.h"
#include "ArtPiece.h"

// Sets default values
APropManipulator::APropManipulator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APawn* Player = PlayerController ? PlayerController->GetPawn() : nullptr;
	AActor* ArtPiece = UGameplayStatics::GetActorOfClass(GetWorld(), AArtPiece::StaticClass());

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
		ArtPiece->SetActorRotation(HitResult.ImpactNormal.Rotation());
	}
}

