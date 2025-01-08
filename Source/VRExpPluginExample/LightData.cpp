// Fill out your copyright notice in the Description page of Project Settings.


#include "LightData.h"
#include "GalleryLight.h"

ULightData::ULightData()
{
}

ULightData::~ULightData()
{
}

FString ULightData::GetPropName_Implementation()
{
    return Name;
}

AActor* ULightData::SpawnActor_Implementation(UObject* ActorInWorld, FTransform Transform)
{
	UWorld* World = ActorInWorld->GetWorld();
	AGalleryLight* SpawnedModel = World->SpawnActor<AGalleryLight>(AGalleryLight::StaticClass(), Transform);
	SpawnedModel->SetMesh(mesh);

	switch (LightType)
	{
	case ELightType::Point:
		SpawnedModel->AddPointLight();
		break;
	case ELightType::Spot:
		SpawnedModel->AddSpotLight();
		break;
	case ELightType::Rect:
		SpawnedModel->AddRectLight();
		break;
	default:
		break;
	}

	return SpawnedModel;
}

FTransform ULightData::GetDefaultTransform_Implementation()
{
    return FTransform();
}
