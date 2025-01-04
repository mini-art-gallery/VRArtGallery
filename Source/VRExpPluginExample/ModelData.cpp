// Fill out your copyright notice in the Description page of Project Settings.


#include "ModelData.h"

UModelData::UModelData()
{
	Name = FString("Default Model");
}

UModelData::~UModelData()
{
}


FString UModelData::GetPropName_Implementation()
{
	return Name;
}

AActor* UModelData::SpawnActor_Implementation(UObject* ActorInWorld, FTransform Transform) {
	UWorld* World = ActorInWorld->GetWorld();
	AGalleryModel* SpawnedModel = World->SpawnActor<AGalleryModel>(AGalleryModel::StaticClass(), Transform);
	SpawnedModel->SetMesh(mesh);
	return SpawnedModel;
}

FTransform UModelData::GetDefaultTransform_Implementation() {
	FTransform Transform;
	return Transform;
}