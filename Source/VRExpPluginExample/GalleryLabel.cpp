// Fill out your copyright notice in the Description page of Project Settings.


#include "GalleryLabel.h"


// Sets default values
AGalleryLabel::AGalleryLabel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGalleryLabel::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGalleryLabel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGalleryLabel::SetMesh(UStaticMesh* mesh)
{
	MeshComponent->SetStaticMesh(mesh);
}