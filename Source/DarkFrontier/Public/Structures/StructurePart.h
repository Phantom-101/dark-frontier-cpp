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

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Action")
	TSubclassOf<class UStructurePartActionGroup> ActionGroupType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Action")
	TSubclassOf<class UStructurePartAction> ActionType;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Action")
	TObjectPtr<class UStructurePartAction> Action;

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
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TArray<TObjectPtr<UStructurePartSlot>> Slots;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION(BlueprintCallable)
	void InitOwningStructure(AStructure* NewOwner);

	UFUNCTION(BlueprintCallable)
	void OnRegistered();

	UFUNCTION(BlueprintCallable)
	void OnUnregistered();

	UFUNCTION(BlueprintCallable)
	void RegisterPartSlot(UStructurePartSlot* Slot);

	static TArray<const UStructurePartSlot*> GetCompatiblePartSlots_CDO(TSubclassOf<AStructurePart> PartClass, const UStructurePartSlot* Other);
	
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

	// Version 2 API

	UFUNCTION(BlueprintCallable, Category="Status")
	bool IsRootPart() const;

	UFUNCTION(BlueprintCallable, Category="Status")
	bool IsActive();

	UFUNCTION(BlueprintCallable, Category="Slots")
	TArray<UStructurePartSlot*> GetSlots();

	UFUNCTION(BlueprintCallable, Category="Slots")
	UStructurePartSlot* GetSlot(FText InName);

	UFUNCTION(BlueprintCallable, Category="Slots")
	TArray<UStructurePartSlot*> GetCompatibleSlots(const UStructurePartSlot* Other);
	
	// Statics

};
