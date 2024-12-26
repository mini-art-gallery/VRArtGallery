// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtWorkData.h"

UArtWorkData::UArtWorkData()
{
	Name = FString("Default Artwork");
	ArtWorkMaterial = nullptr;
}

UArtWorkData::~UArtWorkData()
{
}

FString UArtWorkData::GetPropName_Implementation()
{
	return Name;
}

AActor* UArtWorkData::SpawnActor_Implementation(UObject* ActorInWorld, FTransform Transform) {
	UWorld* World = ActorInWorld->GetWorld();
	AArtPiece* SpawnedArtPiece = World->SpawnActor<AArtPiece>(AArtPiece::StaticClass(), Transform);
	SpawnedArtPiece->SetArtwork(ArtWorkMaterial, Width, Height);
	return SpawnedArtPiece;
}

FTransform UArtWorkData::GetDefaultTransform_Implementation() {
	float ratio = (float)Width / Height;

    FVector NewScale = FVector3d(1.f);

    if (ratio > 1)
        NewScale.Z *= 1 / ratio;
    else
        NewScale.Y *= ratio;

	FTransform Transform;
	Transform.SetScale3D(NewScale);

	return Transform;
}