// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GalleryProp.h"
#include "ArtPiece.h"

#include "ArtWorkData.generated.h"

/**
 * 
 */

UCLASS()
class VREXPPLUGINEXAMPLE_API UArtWorkData: public UObject,  public IGalleryProp
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstanceDynamic* ArtWorkMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Height;

	UArtWorkData();
	~UArtWorkData();

	virtual FString GetPropName_Implementation() override;
	virtual AActor* SpawnActor_Implementation(UObject* ActorInWorld, FTransform Transform) override;
	virtual FTransform GetDefaultTransform_Implementation() override;
};
