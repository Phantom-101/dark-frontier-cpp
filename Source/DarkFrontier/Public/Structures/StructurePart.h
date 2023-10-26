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

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	FText TypeName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	TSubclassOf<class UGameplayEffect> AttributeEffect;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	TObjectPtr<class AStructure> OwningStructure;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	int32 PartId;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	TArray<TObjectPtr<class UStructurePartSlot>> PartSlots;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	int32 DistanceToRoot = -1;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Combat")
	TObjectPtr<class AFaction> ControlledBy;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Combat")
	TArray<TObjectPtr<class UArmy>> Armies;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Combat")
	TArray<TObjectPtr<UArmy>> ArrivingArmies;

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

	UFUNCTION(BlueprintCallable)
	void PropagateDistanceUpdate(int32 Distance);

	UFUNCTION(BlueprintCallable)
	void TickArmies();

	UFUNCTION(BlueprintCallable)
	void ProcessArrivingArmies();

};
