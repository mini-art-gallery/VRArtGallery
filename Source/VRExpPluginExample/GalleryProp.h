// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GalleryProp.generated.h"

/**
 * 
 */
UINTERFACE(Blueprintable)
class VREXPPLUGINEXAMPLE_API UGalleryProp : public UInterface
{
	GENERATED_BODY()
	
};

class VREXPPLUGINEXAMPLE_API IGalleryProp
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GalleryProp")
    FString GetPropName();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GalleryProp")
    AActor* SpawnActor(UObject* ActorInWorld, FTransform Transform);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GalleryProp")
    FTransform GetDefaultTransform();
};
