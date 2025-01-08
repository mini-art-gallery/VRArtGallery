// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GalleryActor.h"
#include "GalleryLight.generated.h"

UCLASS()
class VREXPPLUGINEXAMPLE_API AGalleryLight : public AGalleryActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGalleryLight();

	void SetMesh(UStaticMesh* mesh);

	void AddPointLight();
	void AddSpotLight();
	void AddRectLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
