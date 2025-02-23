// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "DesktopPlatformModule.h"
#include "IPlatformFilePak.h"
#include "Misc/Paths.h"
#include "Engine/Engine.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Texture2D.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "ImageUtils.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "ArtPiece.h"
#include "ArtWorkData.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "ArtworkLoader.generated.h"

UCLASS()
class VREXPPLUGINEXAMPLE_API AArtworkLoader : public AActor
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "ArtworkLoader")
	void LoadArtwork();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Files")
	TArray<FString> Files;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FString OpenFileDialog(const FString FileTypes, const FString DialogTitle);
	UTexture2D* LoadTextureFromFile(const FString& FilePath);
	void CreateArtPiece(UTexture2D* ArtTexture, const FString& name);
};
