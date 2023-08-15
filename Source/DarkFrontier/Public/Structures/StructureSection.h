// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StructureSection.generated.h"

UCLASS()
class DARKFRONTIER_API AStructureSection : public AActor
{
	GENERATED_BODY()
	
public:	

	AStructureSection();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<class UGameplayEffect> AttributeEffect;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AStructure> OwningStructure;

	UPROPERTY(BlueprintReadOnly)
	int32 SectionId;

	UPROPERTY(BlueprintReadOnly);
	TArray<TObjectPtr<class UStructureSectionSlot>> SectionSlots;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<class UStructureEquipmentSlot>> EquipmentSlots;

protected:

	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void InitOwningStructure(AStructure* NewOwner);

	UFUNCTION(BlueprintCallable)
	void RegisterSectionSlot(UStructureSectionSlot* Slot);

	UFUNCTION(BlueprintCallable)
	UStructureSectionSlot* GetSectionSlotByName(FText Name);

	UFUNCTION(BlueprintCallable)
	TArray<UStructureSectionSlot*> GetCompatibleSectionSlots(TSubclassOf<class UStructureSectionSlotType> SlotType);

	UFUNCTION(BlueprintCallable)
	void AttachNearbySectionSlots();

	UFUNCTION(BlueprintCallable)
	void RegisterEquipmentSlot(UStructureEquipmentSlot* Slot);

	UFUNCTION(BlueprintCallable)
	UStructureEquipmentSlot* GetEquipmentSlotByName(FText Name);

	UFUNCTION(BlueprintCallable)
	void RemoveSection();

};
