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

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	FText SlotName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	TObjectPtr<class UStructurePartSlotType> SlotType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Instanced, Category="Setup")
	TObjectPtr<class UStructurePartSlotFilter> Filter;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AStructurePart> OwningPart;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UStructurePartSlot> AttachedSlot;

protected:
	
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	bool CanAttach(const UStructurePartSlot* Other) const;

	UFUNCTION(BlueprintCallable)
	bool TryAttach(UStructurePartSlot* NewSlot);
	
	UFUNCTION(BlueprintCallable)
	bool TryDetach();

protected:

	UFUNCTION(BlueprintCallable)
	void MatchTransform(UStructurePartSlot* Other);
	
};
