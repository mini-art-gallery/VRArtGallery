// Fill out your copyright notice in the Description page of Project Settings.


#include "GalleryLabel.h"


// Sets default values
AGalleryLabel::AGalleryLabel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComponent"));
	TextComponent->SetupAttachment(RootComponent);
	TextComponent->SetIsReplicated(true);
	TextComponent->SetRelativeLocation(FVector3d(10, 6, 30));
	TextComponent->SetWorldRotation(FRotator3d(120, 0, 0));
	TextComponent->SetWorldScale3D(FVector3d(0.3));

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

void AGalleryLabel::UpdateText(FString Text)
{
	int lines = 0;
	for (int i = 0; i < Text.Len(); i++)
		if (Text[i] == '\n') lines++;
	
	int maxLine = 0;
	int currLine = 0;
	for (int i = 0; i < Text.Len(); i++) {
		currLine++;
		if (Text[i] == '\n') {
			if (maxLine < currLine) maxLine = currLine;
			currLine = 0;
		}
	}
	if (maxLine < currLine) maxLine = currLine;

	
	TextComponent->SetRelativeLocation(FVector3d(10 + lines*6, 1.5*maxLine, 30 + lines * 3));


	auto text = FText::FromString(Text);
	TextComponent->SetText(text);
}

FString AGalleryLabel::GetText()
{
	return TextComponent->Text.ToString();
}