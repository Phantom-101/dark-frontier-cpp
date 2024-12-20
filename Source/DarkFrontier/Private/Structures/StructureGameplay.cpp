// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureGameplay.h"
#include "Gameplay/Attributes/EnergyAttributeSet.h"
#include "Gameplay/Attributes/HullAttributeSet.h"
#include "Gameplay/Attributes/LayoutAttributeSet.h"
#include "Gameplay/Attributes/ShieldAttributeSet.h"
#include "Gameplay/Attributes/DetectionAttributeSet.h"
#include "Structures/Structure.h"
#include "Structures/StructureAbility.h"
#include "Structures/StructureAbilitySystemComponent.h"

UStructureGameplay* UStructureGameplay::CreateGameplay(AStructure* Structure)
{
	UStructureGameplay* Gameplay = Structure->CreateDefaultSubobject<UStructureGameplay>("Gameplay");
	
	Gameplay->AbilitySystemComponent = Structure->CreateDefaultSubobject<UStructureAbilitySystemComponent>("AbilitySystemComponent");
	Gameplay->AbilitySystemComponent->SetIsReplicated(true);
	Gameplay->AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Gameplay->HullAttributes = Structure->CreateDefaultSubobject<UHullAttributeSet>("HullAttributes");
	Gameplay->ShieldAttributes = Structure->CreateDefaultSubobject<UShieldAttributeSet>("ShieldAttributes");
	Gameplay->EnergyAttributes = Structure->CreateDefaultSubobject<UEnergyAttributeSet>("EnergyAttributes");
	Gameplay->LayoutAttributes = Structure->CreateDefaultSubobject<ULayoutAttributeSet>("LayoutAttributes");
	Gameplay->DetectionAttributes = Structure->CreateDefaultSubobject<UDetectionAttributeSet>("DetectionAttributes");
	Gameplay->MobilityAttributes = Structure->CreateDefaultSubobject<UMobilityAttributeSet>("MobilityAttributes");

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
	const float Detection = DetectionAttributes->GetDetection() * Other->GetGameplay()->GetDetectability();
	return SquareLength <= Detection;
}

void UStructureGameplay::ApplyStartingEffects()
{
	for(const TSubclassOf<UGameplayEffect> StartingEffect : StartingEffects)
	{
		(void)ApplyEffect(StartingEffect);
	}
}
