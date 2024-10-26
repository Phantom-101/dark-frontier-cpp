// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureGameplay.h"
#include "Gameplay/Attributes/EnergyAttributeSet.h"
#include "Gameplay/Attributes/IntegrityAttributeSet.h"
#include "Gameplay/Attributes/LayoutAttributeSet.h"
#include "Gameplay/Attributes/ResistanceAttributeSet.h"
#include "Gameplay/Attributes/ShieldAttributeSet.h"
#include "Gameplay/Attributes/DetectabilityAttributeSet.h"
#include "Structures/Structure.h"
#include "Structures/StructureAbility.h"
#include "Structures/StructureAbilitySystemComponent.h"
#include "Structures/StructureAttributeSet.h"

UStructureGameplay* UStructureGameplay::CreateGameplay(AStructure* Structure)
{
	UStructureGameplay* Gameplay = Structure->CreateDefaultSubobject<UStructureGameplay>("Gameplay");
	
	Gameplay->AbilitySystemComponent = Structure->CreateDefaultSubobject<UStructureAbilitySystemComponent>("AbilitySystemComponent");
	Gameplay->AbilitySystemComponent->SetIsReplicated(true);
	Gameplay->AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Gameplay->IntegrityAttributes = Structure->CreateDefaultSubobject<UIntegrityAttributeSet>("IntegrityAttributes");
	Gameplay->ResistanceAttributes = Structure->CreateDefaultSubobject<UResistanceAttributeSet>("ResistanceAttributes");
	Gameplay->ShieldAttributes = Structure->CreateDefaultSubobject<UShieldAttributeSet>("ShieldAttributes");
	Gameplay->EnergyAttributes = Structure->CreateDefaultSubobject<UEnergyAttributeSet>("EnergyAttributes");
	Gameplay->LayoutAttributes = Structure->CreateDefaultSubobject<ULayoutAttributeSet>("LayoutAttributes");
	Gameplay->DetectabilityAttributes = Structure->CreateDefaultSubobject<UDetectabilityAttributeSet>("SignatureAttributes");
	Gameplay->AttributeSet = Structure->CreateDefaultSubobject<UStructureAttributeSet>("AttributeSet");

	return Gameplay;
}

AStructure* UStructureGameplay::GetStructure() const
{
	return Cast<AStructure>(GetActor());
}

UStructureAbilitySystemComponent* UStructureGameplay::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

bool UStructureGameplay::IsDetecting(AStructure* Other) const
{
	const double SquareLength = (GetStructure()->GetActorLocation() - Other->GetActorLocation()).SquaredLength();
	const float Detection = AttributeSet->GetSensorStrength() * Other->GetGameplay()->GetRadarCrossSection();
	return SquareLength <= Detection;
}

void UStructureGameplay::ApplyStartingEffects()
{
	for(const TSubclassOf<UGameplayEffect> StartingEffect : StartingEffects)
	{
		(void)ApplyEffect(StartingEffect);
	}
}
