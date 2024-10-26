// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Subactors/StructureShield.h"
#include "Engine/DamageEvents.h"
#include "Structures/Damage/StructureDamageType.h"
#include "Structures/Subactors/StructureShieldGameplay.h"

AStructureShield::AStructureShield()
{
	PrimaryActorTick.bCanEverTick = true;

	Gameplay = UStructureShieldGameplay::CreateGameplay(this);
}

UStructureShieldGameplay* AStructureShield::GetGameplay()
{
	return Gameplay;
}

float AStructureShield::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// Calculate damage based on damage event type and fire event dispatchers
	// The value provided to event listeners is the raw damage before resistances are applied
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	const UDamageType* DamageType = DamageEvent.DamageTypeClass ? DamageEvent.DamageTypeClass.GetDefaultObject() : GetDefault<UDamageType>();
	const UStructureDamageType* StructureDamageType = Cast<UStructureDamageType>(DamageType);

	// Healing is not supported
	if(DamageAmount > 0)
	{
		const float Multiplier = StructureDamageType ? StructureDamageType->GetMultiplier(Gameplay->GetAbilitySystemComponent()) : 1;
		const float Equivalent = Gameplay->GetIntegrity() / Multiplier;
		const float Absorbed = FMath::Min(DamageAmount, Equivalent);
		const float Damage = Absorbed * Multiplier;
		
		Gameplay->SetIntegrity(Gameplay->GetIntegrity() - Damage);
		
		// Return the actual amount absorbed
		return Absorbed;
	}

	return 0;
}
