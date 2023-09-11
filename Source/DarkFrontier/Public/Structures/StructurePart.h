// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StructurePart.generated.h"

UCLASS()
class DARKFRONTIER_API AStructurePart : public AActor
{
	GENERATED_BODY()
	
public:	

	AStructurePart();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<class UGameplayEffect> AttributeEffect;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AStructure> OwningStructure;

	UPROPERTY(BlueprintReadOnly)
	int32 PartId;

	UPROPERTY(BlueprintReadOnly);
	TArray<TObjectPtr<class UStructurePartSlot>> PartSlots;

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION(BlueprintCallable)
	void InitOwningStructure(AStructure* NewOwner);

	UFUNCTION(BlueprintCallable)
	void RegisterPartSlot(UStructurePartSlot* Slot);

	UFUNCTION(BlueprintCallable)
	UStructurePartSlot* GetPartSlotByName(FText Name);

	UFUNCTION(BlueprintCallable)
	TArray<UStructurePartSlot*> GetCompatiblePartSlots(TSubclassOf<class UStructurePartSlotType> SlotType);

	UFUNCTION(BlueprintCallable)
	void AttachNearbyPartSlots();

	UFUNCTION(BlueprintCallable)
	void RemovePart();

};
