// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/GameplaySubobject.h"
#include "Gameplay/Attributes/AttributeMacros.h"
#include "Gameplay/Attributes/IntegrityAttributeSet.h"
#include "Gameplay/Attributes/ResistanceAttributeSet.h"
#include "UObject/Object.h"
#include "StructureShieldGameplay.generated.h"

class AStructureShield;
class UStructureAbilitySystemComponent;
class UGameplayEffect;

/**
 * 
 */
UCLASS(DefaultToInstanced)
class DARKFRONTIER_API UStructureShieldGameplay : public UGameplaySubobject
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>> StartingEffects;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UStructureAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UIntegrityAttributeSet> IntegrityAttributes;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UResistanceAttributeSet> ResistanceAttributes;

public:

	static UStructureShieldGameplay* CreateGameplay(AStructureShield* Shield);
	
	UFUNCTION(BlueprintCallable)
	AStructureShield* GetShield() const;
	
	UFUNCTION(BlueprintCallable)
	virtual UStructureAbilitySystemComponent* GetAbilitySystemComponent() const override;

	ATTRIBUTE_PASSTHROUGH(IntegrityAttributes, MaxIntegrity);
	ATTRIBUTE_PASSTHROUGH(IntegrityAttributes, Integrity);
	ATTRIBUTE_PASSTHROUGH_WithPrefix(IntegrityAttributes, Regeneration, Integrity);

	ATTRIBUTE_PASSTHROUGH(ResistanceAttributes, KineticResistance);
	ATTRIBUTE_PASSTHROUGH(ResistanceAttributes, ExplosiveResistance);
	ATTRIBUTE_PASSTHROUGH(ResistanceAttributes, ThermalResistance);
	ATTRIBUTE_PASSTHROUGH(ResistanceAttributes, ElectromagneticResistance);

	UFUNCTION(BlueprintCallable)
	void ApplyStartingEffects();

};
