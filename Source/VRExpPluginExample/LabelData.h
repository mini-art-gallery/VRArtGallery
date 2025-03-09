#pragma once

#include "CoreMinimal.h"
#include "GalleryProp.h"
#include "GalleryLabel.h"
#include "Components/StaticMeshComponent.h"

#include "LabelData.generated.h"




UCLASS(BlueprintType)
class VREXPPLUGINEXAMPLE_API ULabelData : public UObject, public IGalleryProp
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* mesh;

	ULabelData();
	~ULabelData();

	virtual FString GetPropName_Implementation() override;
	virtual AActor* SpawnActor_Implementation(UObject* ActorInWorld, FTransform Transform) override;
	virtual FTransform GetDefaultTransform_Implementation() override;
};

