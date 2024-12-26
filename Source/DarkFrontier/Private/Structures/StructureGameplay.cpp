// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureGameplay.h"
#include "Log.h"
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

void UStructureGameplay::Initialize() const
{
	AActor* Actor = Cast<AActor>(GetOuter());
	GetAbilitySystemComponent()->InitAbilityActorInfo(Actor, Actor);
}

AStructure* UStructureGameplay::GetStructure() const
{
	return Cast<AStructure>(GetOuter());
}

FActiveGameplayEffectHandle UStructureGameplay::ApplyEffect(const TSubclassOf<UGameplayEffect> Effect) const
{
	Initialize();
	if(IsValid(Effect))
	{
		UStructureAbilitySystemComponent* Comp = GetAbilitySystemComponent();
		
		FGameplayEffectContextHandle EffectContext = Comp->MakeEffectContext();
		EffectContext.AddSourceObject(GetStructure());

		const FGameplayEffectSpecHandle SpecHandle = Comp->MakeOutgoingSpec(Effect, 1, EffectContext);

		if(SpecHandle.IsValid())
		{
			const FActiveGameplayEffectHandle EffectHandle = Comp->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
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
		GetAbilitySystemComponent()->RemoveActiveGameplayEffect(Handle);
	}
}

FGameplayAbilitySpecHandle UStructureGameplay::GiveAbility(const TSubclassOf<UStructureAbility> Ability) const
{
	if(GetStructure()->HasAuthority() && IsValid(Ability))
	{
		UStructureAbilitySystemComponent* Comp = GetAbilitySystemComponent();
		
		return Comp->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, Comp));
	}

	return FGameplayAbilitySpecHandle();
}

void UStructureGameplay::ClearAbility(const FGameplayAbilitySpecHandle Handle) const
{
	if(GetStructure()->HasAuthority() && Handle.IsValid())
	{
		GetAbilitySystemComponent()->ClearAbility(Handle);
	}
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
