// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "StructureSectionSlot.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKFRONTIER_API UStructureSectionSlot : public USceneComponent
{
	GENERATED_BODY()

public:

	UStructureSectionSlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UStructureSectionSlotType> SlotType;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AStructureSection> OwningSection;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UStructureSectionSlot> AttachedSlot;

protected:
	
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void Attach(UStructureSectionSlot* NewSlot);

	UFUNCTION(BlueprintCallable)
	void Detach();
	
	UFUNCTION(BlueprintCallable)
	void MatchTransform(UStructureSectionSlot* Other);

	UFUNCTION(BlueprintCallable)
	void PhysicallyAttach(UStructureSectionSlot* NewSlot);
	
};
