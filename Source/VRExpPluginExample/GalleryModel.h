// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "GalleryActor.h"
#include "GalleryModel.generated.h"

UCLASS()
class VREXPPLUGINEXAMPLE_API AGalleryModel : public AGalleryActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGalleryModel();

	void SetMesh(UStaticMesh* mesh);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
