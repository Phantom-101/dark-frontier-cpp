// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/GameplaySubobject.h"
#include "Log.h"
#include "Structures/StructureAbility.h"
#include "Structures/StructureAbilitySystemComponent.h"

void UGameplaySubobject::Initialize() const
{
	GetAbilitySystemComponent()->InitAbilityActorInfo(GetActor(), GetActor());
}

AActor* UGameplaySubobject::GetActor() const
{
	return Cast<AActor>(GetOuter());
}

UStructureAbilitySystemComponent* UGameplaySubobject::GetAbilitySystemComponent() const
{
	return GetActor()->GetComponentByClass<UStructureAbilitySystemComponent>();
}

FActiveGameplayEffectHandle UGameplaySubobject::ApplyEffect(const TSubclassOf<UGameplayEffect> Effect) const
{
	Initialize();
	if(IsValid(Effect))
	{
		UStructureAbilitySystemComponent* Comp = GetAbilitySystemComponent();
		
		FGameplayEffectContextHandle EffectContext = Comp->MakeEffectContext();
		EffectContext.AddSourceObject(GetActor());

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

void UGameplaySubobject::RemoveEffect(const FActiveGameplayEffectHandle Handle) const
{
	if(Handle.IsValid())
	{
		GetAbilitySystemComponent()->RemoveActiveGameplayEffect(Handle);
	}
}

FGameplayAbilitySpecHandle UGameplaySubobject::GiveAbility(const TSubclassOf<UStructureAbility> Ability) const
{
	if(GetActor()->HasAuthority() && IsValid(Ability))
	{
		UStructureAbilitySystemComponent* Comp = GetAbilitySystemComponent();
		
		return Comp->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, Comp));
	}

	return FGameplayAbilitySpecHandle();
}

void UGameplaySubobject::ClearAbility(const FGameplayAbilitySpecHandle Handle) const
{
	if(GetActor()->HasAuthority() && Handle.IsValid())
	{
		GetAbilitySystemComponent()->ClearAbility(Handle);
	}
}
