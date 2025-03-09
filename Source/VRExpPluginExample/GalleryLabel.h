// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "GalleryActor.h"
#include "GalleryLabel.generated.h"

/**
 * 
 */
UCLASS()
class VREXPPLUGINEXAMPLE_API AGalleryLabel : public AGalleryActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* TextComponent;

	// Sets default values for this actor's properties
	AGalleryLabel();

	void SetMesh(UStaticMesh* mesh);

	UFUNCTION(BlueprintCallable, Category = "GalleryLabel")
	void UpdateText(FString Text);

	UFUNCTION(BlueprintCallable, Category = "GalleryLabel")
	FString GetText();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
