#include "GalleryModel.h"

// Sets default values
AGalleryModel::AGalleryModel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetIsReplicated(true);
	MeshComponent->SetCollisionProfileName(TEXT("BlockAll"));


}

void AGalleryModel::SetMesh(UStaticMesh* mesh)
{
	MeshComponent->SetStaticMesh(mesh);
}

// Called when the game starts or when spawned
void AGalleryModel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGalleryModel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

