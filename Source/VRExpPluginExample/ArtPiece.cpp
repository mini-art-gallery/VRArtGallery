// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtPiece.h"

// Sets default values
AArtPiece::AArtPiece()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Create the Static Mesh Component (the frame or surface)
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetIsReplicated(true);

    // Set a default mesh (like a frame or wall)
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CanvasMesh(TEXT("/Script/Engine.StaticMesh'/Game/VRArtGallery/canvasModel.canvasModel'"));
    if (CanvasMesh.Succeeded())
    {
        MeshComponent->SetStaticMesh(CanvasMesh.Object);
    }
}

// Called when the game starts or when spawned
void AArtPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArtPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArtPiece::SetArtwork(UMaterialInstanceDynamic* ArtWorkMaterial, int Width, int Height) {
    if (MeshComponent)
    {
        MeshComponent->SetMaterial(0, ArtWorkMaterial);
    }
}
