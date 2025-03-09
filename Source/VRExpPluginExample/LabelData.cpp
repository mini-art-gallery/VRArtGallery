#include "LabelData.h"

ULabelData::ULabelData()
{
	Name = FString("Default Label");
}

ULabelData::~ULabelData()
{
}


FString ULabelData::GetPropName_Implementation()
{
	return Name;
}

AActor* ULabelData::SpawnActor_Implementation(UObject* ActorInWorld, FTransform Transform) {
	UWorld* World = ActorInWorld->GetWorld();
	AGalleryLabel* SpawnedModel = World->SpawnActor<AGalleryLabel>(AGalleryLabel::StaticClass(), Transform);
	SpawnedModel->SetMesh(mesh);
	return SpawnedModel;
}

FTransform ULabelData::GetDefaultTransform_Implementation() {
	FTransform Transform;
	return Transform;
}