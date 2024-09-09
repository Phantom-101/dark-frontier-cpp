// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureGameplay.h"
#include "Log.h"
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

UStructureAttributeSet* UStructureGameplay::GetAttributeSet() const
{
	return AttributeSet;
}

float UStructureGameplay::GetMaxHull() const
{
	return AttributeSet->GetMaxHull() == 0 ? 1 : AttributeSet->GetMaxHull();
}

float UStructureGameplay::GetHull() const
{
	return AttributeSet->GetHull();
}

void UStructureGameplay::SetHull(const float InHull) const
{
	AttributeSet->SetHull(FMath::Clamp(InHull, 0, AttributeSet->GetMaxHull()));
}

float UStructureGameplay::GetMaxShield() const
{
	return AttributeSet->GetMaxShield() == 0 ? 1 : AttributeSet->GetMaxShield();
}

float UStructureGameplay::GetShield() const
{
	return AttributeSet->GetShield();
}

void UStructureGameplay::SetShield(const float InShield) const
{
	AttributeSet->SetShield(FMath::Clamp(InShield, 0, AttributeSet->GetMaxShield()));
}

float UStructureGameplay::GetMaxEnergy() const
{
	return AttributeSet->GetMaxEnergy() == 0 ? 1 : AttributeSet->GetMaxEnergy();
}

float UStructureGameplay::GetEnergy() const
{
	return AttributeSet->GetEnergy();
}

float UStructureGameplay::GetUpkeep() const
{
	return AttributeSet->GetUpkeep() / (AttributeSet->GetUpkeepReduction() + 1);
}

float UStructureGameplay::GetLinearMaxSpeed() const
{
	return AttributeSet->GetLinearMaxSpeed() == 0 ? 1 : AttributeSet->GetLinearMaxSpeed();
}

float UStructureGameplay::GetLinearSpeed() const
{
	return GetStructure()->GetComponentByClass<UStaticMeshComponent>()->GetPhysicsLinearVelocity().Length();
}

bool UStructureGameplay::IsDetecting(AStructure* Other) const
{
	const double SquareLength = (GetStructure()->GetActorLocation() - Other->GetActorLocation()).SquaredLength();
	const float Detection = AttributeSet->GetSensorStrength() * Other->GetGameplay()->AttributeSet->GetSignatureVisibility();
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
