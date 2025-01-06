// Fill out your copyright notice in the Description page of Project Settings.


#include "GalleryActor.h"

// Sets default values
AGalleryActor::AGalleryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGalleryActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGalleryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

