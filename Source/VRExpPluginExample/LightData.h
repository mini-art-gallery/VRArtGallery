// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GalleryProp.h"

#include "LightData.generated.h"

UENUM(BlueprintType)
enum class ELightType : uint8
{
    Point,
    Spot,
    Rect
};

UCLASS(BlueprintType)
class VREXPPLUGINEXAMPLE_API ULightData : public UObject, public IGalleryProp
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ELightType LightType;

	ULightData();
	~ULightData();

	virtual FString GetPropName_Implementation() override;
	virtual AActor* SpawnActor_Implementation(UObject* ActorInWorld, FTransform Transform) override;
	virtual FTransform GetDefaultTransform_Implementation() override;
};
