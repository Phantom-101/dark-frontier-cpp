// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureDamageType.h"
#include "Macros.h"
#include "Engine/DamageEvents.h"

const UStructureDamageType* UStructureDamageType::GetDamageTypeFromEvent(const FDamageEvent& DamageEvent)
{
	GUARD_RETURN(DamageEvent.DamageTypeClass, GetDefault<UStructureDamageType>());
	const UStructureDamageType* DamageType = Cast<UStructureDamageType>(DamageEvent.DamageTypeClass.GetDefaultObject());
	GUARD_RETURN(IsValid(DamageType), GetDefault<UStructureDamageType>());
	return DamageType;
}
