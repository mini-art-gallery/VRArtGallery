// Fill out your copyright notice in the Description page of Project Settings.


#include "IOFile.h"

// Sets default values
AIOFile::AIOFile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIOFile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIOFile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FRoom AIOFile::LoadRoom() {
	return FRoom(10, 5, 12, "not_empty");
}

void AIOFile::LoadActors(FString FileName) {
	if (FileName.IsEmpty()) {
		return;
	}


}
