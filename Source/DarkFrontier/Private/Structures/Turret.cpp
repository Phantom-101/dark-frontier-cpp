// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Turret.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Structures/Structure.h"
#include "Structures/StructureGameplay.h"
#include "Structures/TurretAbility.h"
#include "Structures/TurretPayload.h"
#include "Structures/TurretSource.h"

void ATurret::BeginPlay()
{
	Super::BeginPlay();

	GetComponents<UTurretSource>(Sources);
}

void ATurret::OnAdded(AStructure* Structure)
{
	Super::OnAdded(Structure);

	if(GetAbilityClass() != nullptr)
	{
		AbilityHandle = OwningStructure->GetGameplay()->GiveAbility(GetAbilityClass());
	}
}

void ATurret::OnRemoved()
{
	Super::OnRemoved();

	if(AbilityHandle.IsValid())
	{
		OwningStructure->GetGameplay()->ClearAbility(AbilityHandle);
		AbilityHandle = FGameplayAbilitySpecHandle();
	}
}

TSubclassOf<UTurretAbility> ATurret::GetAbilityClass()
{
	return nullptr;
}

bool ATurret::CanActivate()
{
	for(UTurretSource* SourceTransform : Sources)
	{
		if(CanActivateSource(SourceTransform))
		{
			return true;
		}
	}
	return false;
}

void ATurret::TryActivate()
{
	// Activate each source transform
	for(UTurretSource* SourceTransform : Sources)
	{
		if(CanActivateSource(SourceTransform))
		{
			TryActivateSource(SourceTransform);
		}
	}
}

bool ATurret::CanActivateSource(UTurretSource* Source)
{
	const FGameplayAbilityActorInfo* ActorInfo = GetOwningStructure()->GetAbilitySystemComponent()->AbilityActorInfo.Get();
	return IsValid(GetOwningStructure()->GetTarget()) && GetAbilityClass() != nullptr && GetAbilityClass()->GetDefaultObject<UTurretAbility>()->CanActivateAbility(AbilityHandle, ActorInfo);
}

bool ATurret::TryActivateSource(UTurretSource* Source)
{
	if(GetOwningStructure()->GetAbilitySystemComponent()->TryActivateAbility(AbilityHandle))
	{
		UTurretPayload* Payload = NewObject<UTurretPayload>();
		Payload->Instigator = GetOwningStructure();
		Payload->Turret = this;
		Payload->Source = Source;
		Payload->Target = GetOwningStructure()->GetTarget();
		SendPayload(PayloadTag, Payload);
		return true;
	}
	return false;
}

void ATurret::SendPayload(const FGameplayTag Tag, UObject* Obj) const
{
	FGameplayEventData Payload;
	Payload.Instigator = GetOwningStructure();
	Payload.OptionalObject = Obj;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningStructure(), Tag, Payload);
}
