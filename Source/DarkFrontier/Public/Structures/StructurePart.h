// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
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
	TSubclassOf<class UGameplayEffect> PassiveEffect;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	TObjectPtr<class AStructure> OwningStructure;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	TArray<TObjectPtr<class UStructurePartSlot>> Slots;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	int32 PartId = -1;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	int32 RootDistance = -1;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Gameplay")
	FActiveGameplayEffectHandle PassiveEffectHandle;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Combat")
	TObjectPtr<class AFaction> OwningFaction;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Combat")
	TArray<TObjectPtr<class UCombatant>> Combatants;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Combat")
	TArray<TObjectPtr<UCombatant>> QueuedCombatants;

protected:
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION(BlueprintCallable, Category="Lifetime")
	bool TryInit(AStructure* NewOwner);

	UFUNCTION(BlueprintCallable, Category="Lifetime")
	void OnRegistered();

	UFUNCTION(BlueprintCallable, Category="Lifetime")
	void OnUnRegistered();

	UFUNCTION(BlueprintCallable, Category="State")
	bool IsRootPart() const;

	UFUNCTION(BlueprintCallable, Category="State")
	bool IsActive();

	UFUNCTION(BlueprintCallable, Category="Layout")
	TArray<UStructurePartSlot*> GetSlots();

	UFUNCTION(BlueprintCallable, Category="Layout")
	TArray<UStructurePartSlot*> GetCompatibleSlots(const UStructurePartSlot* Other);

	UFUNCTION(BlueprintCallable, Category="Layout")
	UStructurePartSlot* GetSlot(FText InName);

	UFUNCTION(BlueprintCallable, Category="Layout")
	void AttachSlots();

	UFUNCTION(BlueprintCallable, Category="Layout")
	void DetachSlots();

	UFUNCTION(BlueprintCallable, Category="Layout")
	void UpdateDistance(int32 Distance);

	UFUNCTION(BlueprintCallable, Category="Combat")
	void TickCombatants();

	UFUNCTION(BlueprintCallable, Category="Combat")
	void DequeueCombatants();

	static TArray<const UStructurePartSlot*> GetSlots_CDO(TSubclassOf<AStructurePart> PartClass);

	static TArray<const UStructurePartSlot*> GetCompatibleSlots_CDO(TSubclassOf<AStructurePart> PartClass, const UStructurePartSlot* Other);

	static const UStructurePartSlot* GetSlot_CDO(TSubclassOf<AStructurePart> PartClass, FText InName);

};
