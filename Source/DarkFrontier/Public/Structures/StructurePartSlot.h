// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "StructurePartSlot.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKFRONTIER_API UStructurePartSlot : public USceneComponent
{
	GENERATED_BODY()

public:

	UStructurePartSlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UStructurePartSlotType> SlotType;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AStructurePart> OwningPart;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UStructurePartSlot> AttachedSlot;

protected:
	
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void Attach(UStructurePartSlot* NewSlot);

	UFUNCTION(BlueprintCallable)
	void Detach();
	
	UFUNCTION(BlueprintCallable)
	void MatchTransform(UStructurePartSlot* Other);

	UFUNCTION(BlueprintCallable)
	void PhysicallyAttach(UStructurePartSlot* NewSlot);
	
};
