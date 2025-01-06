// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GalleryActor.generated.h"

UCLASS()
class VREXPPLUGINEXAMPLE_API AGalleryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGalleryActor();


    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bNearPlayer;

    // Sphere component
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* ProximitySphere;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* MeshComponent;

    // Overlap events
    UFUNCTION()
    void OnPlayerEnterProximity(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnPlayerExitProximity(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
