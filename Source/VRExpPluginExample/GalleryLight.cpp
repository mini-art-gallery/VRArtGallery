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
        PointLight->SetIntensity(2500);
        PointLight->SetLightColor(FColor(253, 244, 220));
        PointLight->SetAttenuationRadius(5000.f);
        PointLight->SetVisibility(true);
        Light = PointLight;
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
        SpotLight->SetIntensity(0);
        SpotLight->SetLightColor(FColor(253, 244, 220));
        SpotLight->SetOuterConeAngle(45.f);
        SpotLight->SetInnerConeAngle(30.f);
        SpotLight->SetVisibility(true);
        Light = SpotLight;
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
        RectLight->SetIntensity(250000);
        RectLight->SetIntensityUnits(ELightUnits::Lumens);
        RectLight->SetLightColor(FColor(253, 244, 220));
        RectLight->SetSourceWidth(200.0f);
        RectLight->SetSourceHeight(100.0f);
        RectLight->SetAttenuationRadius(10000.0f);
        RectLight->SetMobility(EComponentMobility::Movable);
        RectLight->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
        RectLight->SetVisibility(true);
        Light = RectLight;
    }
}

void AGalleryLight::UpdateIntensity(float Intensity)
{
    if (Light)
    {

        if (UPointLightComponent* Point = Cast<UPointLightComponent>(Light)) {
            Light->SetIntensity(Intensity*0.01);
        }
        else {
            Light->SetIntensity(Intensity);
        }
    }
}

float AGalleryLight::GetIntensity()
{
    if (Light)
    {

        if (UPointLightComponent* Point = Cast<UPointLightComponent>(Light)) {
           return Light->Intensity * 100;
        }
        else {
            return Light->Intensity;
        }
    }
    return 0;
}