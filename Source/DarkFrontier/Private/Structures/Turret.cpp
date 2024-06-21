// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Turret.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Structures/Structure.h"
#include "Structures/TurretAbility.h"
#include "Structures/TurretPayload.h"
#include "UI/Screens/GameUI/TurretAbilityProxy.h"

void ATurret::OnRegistered()
{
	Super::OnRegistered();

	AbilityHandle = OwningStructure->GiveAbility(Ability);
}

void ATurret::OnUnRegistered()
{
	Super::OnUnRegistered();

	if(AbilityHandle.IsValid())
	{
		OwningStructure->ClearAbility(AbilityHandle);
		AbilityHandle = FGameplayAbilitySpecHandle();
	}
}

int ATurret::TryActivate()
{
	int Activated = 0;

	// Activate each source transform
	for(USceneComponent* SourceTransform : SourceTransforms)
	{
		if(CanActivateSource(SourceTransform))
		{
			ActivateSource(SourceTransform);
			Activated++;
		}
	}

	// Call event function with number of sources successfully activated
	OnActivated(Activated);

	return Activated;
}

void ATurret::OnActivated(int Activated)
{
}

bool ATurret::CanActivateSource(USceneComponent* SourceTransform)
{
	return IsValid(GetOwningStructure()->GetTarget());
}

void ATurret::ActivateSource(USceneComponent* SourceTransform)
{
	if(GetOwningStructure()->GetAbilitySystemComponent()->TryActivateAbility(AbilityHandle))
	{
		UTurretPayload* Payload = NewObject<UTurretPayload>();
		Payload->Instigator = GetOwningStructure();
		Payload->Turret = this;
		Payload->SourceTransform = SourceTransform;
		Payload->Target = GetOwningStructure()->GetTarget();
		SendPayload(PayloadTag, Payload);
	}
}

void ATurret::SendPayload(const FGameplayTag Tag, UObject* Obj) const
{
	FGameplayEventData Payload;
	Payload.Instigator = GetOwningStructure();
	Payload.OptionalObject = Obj;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningStructure(), Tag, Payload);
}
