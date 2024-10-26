// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Subactors/StructureShieldGameplay.h"
#include "Structures/StructureAbility.h"
#include "Structures/StructureAbilitySystemComponent.h"
#include "Structures/Subactors/StructureShield.h"

UStructureShieldGameplay* UStructureShieldGameplay::CreateGameplay(AStructureShield* Shield)
{
	UStructureShieldGameplay* Gameplay = Shield->CreateDefaultSubobject<UStructureShieldGameplay>("Gameplay");
	
	Gameplay->AbilitySystemComponent = Shield->CreateDefaultSubobject<UStructureAbilitySystemComponent>("AbilitySystemComponent");
	Gameplay->AbilitySystemComponent->SetIsReplicated(true);
	Gameplay->AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Gameplay->IntegrityAttributes = Shield->CreateDefaultSubobject<UIntegrityAttributeSet>("IntegrityAttributes");
	Gameplay->ResistanceAttributes = Shield->CreateDefaultSubobject<UResistanceAttributeSet>("ResistanceAttributes");
	
	return Gameplay;
}

AStructureShield* UStructureShieldGameplay::GetShield() const
{
	return Cast<AStructureShield>(GetActor());
}

UStructureAbilitySystemComponent* UStructureShieldGameplay::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void UStructureShieldGameplay::ApplyStartingEffects()
{
	for(const TSubclassOf<UGameplayEffect> StartingEffect : StartingEffects)
	{
		(void)ApplyEffect(StartingEffect);
	}
}
