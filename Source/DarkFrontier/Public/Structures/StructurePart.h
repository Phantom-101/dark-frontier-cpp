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

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	FText TypeName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	TSubclassOf<class UGameplayEffect> PassiveEffect;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	TObjectPtr<class AStructure> OwningStructure;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	TArray<TObjectPtr<class UStructureSlot>> Slots;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	FString PartId;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	int32 RootDistance = -1;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Gameplay")
	TObjectPtr<class AFaction> OwningFaction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Gameplay")
	TArray<TObjectPtr<class UCombatant>> Combatants;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Gameplay")
	TArray<TObjectPtr<UCombatant>> QueuedCombatants;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Gameplay")
	FActiveGameplayEffectHandle PassiveEffectHandle;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION(BlueprintCallable, Category="Prototype")
	FText GetTypeName() const;

	UFUNCTION(BlueprintCallable, Category="Prototype")
	TSubclassOf<UGameplayEffect> GetPassiveEffect() const;
	
	UFUNCTION(BlueprintCallable, Category="Lifetime")
	bool TryInit(AStructure* NewOwner, bool RegisterOnly = false);

	UFUNCTION(BlueprintCallable, Category="Lifetime")
	virtual void OnRegistered();

	UFUNCTION(BlueprintCallable, Category="Lifetime")
	virtual void OnUnRegistered();

	UFUNCTION(BlueprintCallable, Category="Layout")
	AStructure* GetOwningStructure() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	bool IsRootPart() const;
	
	UFUNCTION(BlueprintCallable, Category="Layout")
	FString GetPartId() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	bool TryInitPartId(FString InId);

	UFUNCTION(BlueprintCallable, Category="Layout")
	int GetRootDistance() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	void ResetRootDistance();

	UFUNCTION(BlueprintCallable, Category="Layout")
	void UpdateRootDistance(int32 Distance);
	
	UFUNCTION(BlueprintCallable, Category="Layout")
	TArray<UStructureSlot*> GetSlots();

	UFUNCTION(BlueprintCallable, Category="Layout")
	TArray<UStructureSlot*> GetCompatibleSlots(const UStructureSlot* Other);

	UFUNCTION(BlueprintCallable, Category="Layout")
	UStructureSlot* GetSlot(FText InName);

	UFUNCTION(BlueprintCallable, Category="Layout")
	void AttachSlots();

	UFUNCTION(BlueprintCallable, Category="Layout")
	void DetachSlots();

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual void AddAbilitiesToProxyGroups(TArray<class UStructureAbilityProxyGroup*>& ProxyGroups);

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void AddAbilityToProxyGroups(TArray<UStructureAbilityProxyGroup*>& ProxyGroups, TSubclassOf<class UStructureAbility> AbilityClass, class UStructureAbilityProxy* Proxy) const;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void TickCombatants();

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void DequeueCombatants();

	UFUNCTION(BlueprintCallable, Category="UI")
	virtual class UStructurePartIndicator* CreateIndicator();

	static TArray<const UStructureSlot*> GetSlots_CDO(TSubclassOf<AStructurePart> PartClass);

	static TArray<const UStructureSlot*> GetCompatibleSlots_CDO(TSubclassOf<AStructurePart> PartClass, const UStructureSlot* Other);

	static const UStructureSlot* GetSlot_CDO(TSubclassOf<AStructurePart> PartClass, const FText& InName);

};
