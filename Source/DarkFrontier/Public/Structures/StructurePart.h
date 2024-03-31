// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameFramework/Actor.h"
#include "StructurePart.generated.h"

UCLASS()
class DARKFRONTIER_API AStructurePart : public AActor
{
	GENERATED_BODY()
	
public:	

	AStructurePart();

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	FText TypeName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	TSubclassOf<class UGameplayEffect> PassiveEffect;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	TArray<TSubclassOf<class UStructureGameplayAbility>> Abilities;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	TObjectPtr<class AStructure> OwningStructure;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	TArray<TObjectPtr<class UStructurePartSlot>> Slots;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	FString PartId;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	int32 RootDistance = -1;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Gameplay")
	FActiveGameplayEffectHandle PassiveEffectHandle;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Gameplay")
	TArray<FGameplayAbilitySpecHandle> AbilityHandles;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Combat")
	TObjectPtr<class AFaction> OwningFaction;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Combat")
	TArray<TObjectPtr<class UCombatant>> Combatants;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Combat")
	TArray<TObjectPtr<UCombatant>> QueuedCombatants;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION(BlueprintCallable, Category="Prototype")
	FText GetTypeName() const;

	UFUNCTION(BlueprintCallable, Category="Prototype")
	TSubclassOf<UGameplayEffect> GetPassiveEffect() const;

	UFUNCTION(BlueprintCallable, Category="Prototype")
	TArray<TSubclassOf<class UStructureGameplayAbility>> GetAbilities() const;
	
	UFUNCTION(BlueprintCallable, Category="Lifetime")
	bool TryInit(AStructure* NewOwner, bool RegisterOnly = false);

	UFUNCTION(BlueprintCallable, Category="Lifetime")
	void OnRegistered();

	UFUNCTION(BlueprintCallable, Category="Lifetime")
	void OnUnRegistered();

	UFUNCTION(BlueprintCallable, Category="Layout")
	AStructure* GetOwningStructure() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	bool IsRootPart() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	bool IsActiveInLayout();
	
	UFUNCTION(BlueprintCallable, Category="Layout")
	FString GetPartId() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	bool TryInitPartId(FString InId);

	UFUNCTION(BlueprintCallable, Category="Layout")
	int GetRootDistance() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	void ResetRootDistance();
	
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

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual float GetArcLength(TSubclassOf<UStructureGameplayAbility> AbilityClass);

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual FLinearColor GetArcColor(TSubclassOf<UStructureGameplayAbility> AbilityClass);

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual void ActivateAbility(TSubclassOf<UStructureGameplayAbility> AbilityClass);

	UFUNCTION(BlueprintCallable, Category="Combat")
	void TickCombatants();

	UFUNCTION(BlueprintCallable, Category="Combat")
	void DequeueCombatants();

	static TArray<const UStructurePartSlot*> GetSlots_CDO(TSubclassOf<AStructurePart> PartClass);

	static TArray<const UStructurePartSlot*> GetCompatibleSlots_CDO(TSubclassOf<AStructurePart> PartClass, const UStructurePartSlot* Other);

	static const UStructurePartSlot* GetSlot_CDO(TSubclassOf<AStructurePart> PartClass, FText InName);

};
