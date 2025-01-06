// Fill out your copyright notice in the Description page of Project Settings.


#include "GalleryActor.h"

// Sets default values
AGalleryActor::AGalleryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    bNearPlayer = false;

    // Create the Static Mesh Component (the frame or surface)
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetIsReplicated(true);
    MeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
    RootComponent = MeshComponent;

    ProximitySphere = CreateDefaultSubobject<USphereComponent>(TEXT("ProximitySphere"));
    ProximitySphere->SetupAttachment(MeshComponent);
    
    ProximitySphere->SetSphereRadius(500.0f);
    ProximitySphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ProximitySphere->SetCollisionResponseToAllChannels(ECR_Ignore);
    ProximitySphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    // Bind the overlap events
    ProximitySphere->OnComponentBeginOverlap.AddDynamic(this, &AGalleryActor::OnPlayerEnterProximity);
    ProximitySphere->OnComponentEndOverlap.AddDynamic(this, &AGalleryActor::OnPlayerExitProximity);
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

void AGalleryActor::OnPlayerEnterProximity(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    APawn* Player = PlayerController ? PlayerController->GetPawn() : nullptr;
    if (OtherActor && OtherActor == Player)
    {
        bNearPlayer = true;
        // TODO Activates three times?
        /*if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Player entered proximity!"));
        }*/
    }
}

void AGalleryActor::OnPlayerExitProximity(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    APawn* Player = PlayerController ? PlayerController->GetPawn() : nullptr;
    if (OtherActor && OtherActor == Player)
    {
        bNearPlayer = false;
        /*if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player exited proximity!"));
        }*/
    }
}
