// Fill out your copyright notice in the Description page of Project Settings.


#include "GalleryLight.h"

#include "Components/PointLightComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/RectLightComponent.h"

// Sets default values
AGalleryLight::AGalleryLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGalleryLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGalleryLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGalleryLight::SetMesh(UStaticMesh* mesh)
{
	MeshComponent->SetStaticMesh(mesh);
}

void AGalleryLight::AddPointLight()
{
    UPointLightComponent* PointLight = NewObject<UPointLightComponent>(this, UPointLightComponent::StaticClass());

    if (PointLight)
    {
        PointLight->RegisterComponent();
        PointLight->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
        PointLight->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
        PointLight->SetIntensity(3000000.f);
        PointLight->SetLightColor(FColor::Red);
        PointLight->SetAttenuationRadius(500.f);
        PointLight->SetVisibility(true);
    }
}

void AGalleryLight::AddSpotLight()
{
    USpotLightComponent* SpotLight = NewObject<USpotLightComponent>(this, USpotLightComponent::StaticClass());

    if (SpotLight)
    {
        SpotLight->RegisterComponent(); // Register the component with the engine
        SpotLight->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
        SpotLight->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
        SpotLight->SetIntensity(3000000.f);
        SpotLight->SetLightColor(FColor::Green);
        SpotLight->SetOuterConeAngle(45.f);
        SpotLight->SetInnerConeAngle(30.f);
        SpotLight->SetVisibility(true);
    }
}

void AGalleryLight::AddRectLight()
{
    // Create a new Rect Light component
    URectLightComponent* RectLight = NewObject<URectLightComponent>(this, URectLightComponent::StaticClass());

    if (RectLight)
    {
        RectLight->RegisterComponent();
        RectLight->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
        RectLight->SetIntensity(3000000.f);
        RectLight->SetIntensityUnits(ELightUnits::Lumens);
        RectLight->SetLightColor(FLinearColor::Blue);
        RectLight->SetSourceWidth(200.0f);
        RectLight->SetSourceHeight(100.0f);
        RectLight->SetAttenuationRadius(1000.0f);
        RectLight->SetMobility(EComponentMobility::Movable);
        RectLight->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
        RectLight->SetVisibility(true);
    }
}