#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StructurePartAuthoring.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKFRONTIER_API UStructurePartAuthoring : public UActorComponent
{
	GENERATED_BODY()

public:	

	UStructurePartAuthoring();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AStructurePart> PartClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStructurePartAuthoring> TargetPart;

	UPROPERTY(EditAnywhere)
	FText UseSlot;
	
	UPROPERTY(EditAnywhere)
	FText TargetSlot;

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AStructurePart> AuthoredPart;
	
	virtual void BeginPlay() override;

public:

	AStructurePart* GetAuthoredPart();

};
