// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GalleryProp.h"
#include "Components/StaticMeshComponent.h"
#include "GalleryModel.h"

#include "ModelData.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class VREXPPLUGINEXAMPLE_API UModelData : public UObject, public IGalleryProp
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* mesh;

	UModelData();
	~UModelData();

	virtual FString GetPropName_Implementation() override;
	virtual AActor* SpawnActor_Implementation(UObject* ActorInWorld, FTransform Transform) override;
	virtual FTransform GetDefaultTransform_Implementation() override;
};
