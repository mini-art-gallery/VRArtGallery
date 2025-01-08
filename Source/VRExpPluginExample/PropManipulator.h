// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"

#include "PropManipulator.generated.h"

UCLASS()
class VREXPPLUGINEXAMPLE_API APropManipulator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APropManipulator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TraceRay();

	UFUNCTION(BlueprintCallable, Category = "PropManipulator")
	void PlaceActiveProp();


	UFUNCTION(BlueprintCallable, Category = "PropManipulator")
	AGalleryActor* GetLookedAtActor();

	UFUNCTION(BlueprintCallable, Category = "PropManipulator")
	void ScaleObject(float scale);

	UFUNCTION(BlueprintCallable, Category = "PropManipulator")
	void RotateObject(float degree);

private:
	float propRotation=0;
};
