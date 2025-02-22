// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IOFile.generated.h"

USTRUCT(BlueprintType)
struct FRoom
{
    GENERATED_BODY()

    // Make the variables Blueprint-readable and writable
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Room")
    float Width;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Room")
    float Height;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Room")
    float Length;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Room")
    FString FileName;

    // Default constructor
    FRoom()
        : Width(0), Height(0), Length(0), FileName("")
    {
    }

    // Custom constructor for convenience
    FRoom(float InWidth, float InHeight, float InLength, FString InFileName)
        : Width(InWidth), Height(InHeight), Length(InLength), FileName(InFileName)
    {
    }
};

UCLASS()
class VREXPPLUGINEXAMPLE_API AIOFile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIOFile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "IOFile")
    FRoom LoadRoom();

    UFUNCTION(BlueprintCallable, Category = "IOFile")
    void LoadActors(FString FileName);

    UFUNCTION(BlueprintCallable, Category = "IOFile")
    void SaveScene();

private:
    UTexture2D* LoadTextureFromFile(const FString& FilePath);
    void CreateArtPiece(UTexture2D* ArtTexture, const FString& name);
};
