// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureGameplay.h"
#include "Log.h"
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

void UStructureGameplay::Initialize() const
{
	AbilitySystemComponent->InitAbilityActorInfo(GetStructure(), GetStructure());
}

AStructure* UStructureGameplay::GetStructure() const
{
	return Cast<AStructure>(GetOuter());
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

FActiveGameplayEffectHandle UStructureGameplay::ApplyEffect(const TSubclassOf<UGameplayEffect> Effect) const
{
	Initialize();
	if(IsValid(Effect))
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(GetStructure());

		const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 1, EffectContext);

		if(SpecHandle.IsValid())
		{
			const FActiveGameplayEffectHandle EffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			UE_LOG(LogDarkFrontier, Log, TEXT("Applied effect %s"), *Effect->GetName());
			return EffectHandle;
		}
	}

	return FActiveGameplayEffectHandle();
}

void UStructureGameplay::RemoveEffect(const FActiveGameplayEffectHandle Handle) const
{
	if(Handle.IsValid())
	{
		AbilitySystemComponent->RemoveActiveGameplayEffect(Handle);
	}
}

FGameplayAbilitySpecHandle UStructureGameplay::GiveAbility(const TSubclassOf<UStructureAbility> Ability) const
{
	if(GetStructure()->HasAuthority() && IsValid(Ability))
	{
		return AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, AbilitySystemComponent));
	}

	return FGameplayAbilitySpecHandle();
}

void UStructureGameplay::ClearAbility(const FGameplayAbilitySpecHandle Handle) const
{
	if(GetStructure()->HasAuthority() && Handle.IsValid())
	{
		AbilitySystemComponent->ClearAbility(Handle);
	}
}
