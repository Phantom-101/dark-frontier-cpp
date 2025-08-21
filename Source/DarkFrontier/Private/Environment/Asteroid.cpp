// Fill out your copyright notice in the Description page of Project Settings.

#include "Environment/Asteroid.h"
#include "Macros.h"
#include "Items/ItemPod.h"
#include "Structures/Structure.h"
#include "Structures/StructureDamageType.h"
#include "Structures/StructureLocation.h"

UItem* AAsteroid::GetComposition() const
{
	return Composition;
}

int AAsteroid::GetMaxAmount() const
{
	return MaxAmount;
}

int AAsteroid::GetDepletedAmount() const
{
	return DepletedAmount;
}

FVector AAsteroid::GetTargetLocation()
{
	return GetActorLocation();
}

bool AAsteroid::IsTargetable(AStructure* Structure) const
{
	return Structure->GetLocation()->GetSector() == Sector;
}

TSubclassOf<USelector> AAsteroid::GetSelectorClass() const
{
	return SelectorClass;
}

bool AAsteroid::ShouldShowSelector() const
{
	return true;
}	

float AAsteroid::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	// Calculate damage based on damage event type and fire event dispatchers
	// The value provided to event listeners is the raw damage before multipliers are applied
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	GUARD_RETURN(DamageAmount >= 0, 0);

	const UStructureDamageType* DamageType = UStructureDamageType::GetDamageTypeFromEvent(DamageEvent);

	const float Equivalent = (MaxAmount - DepletedAmount) / DamageType->MiningPower;
	const float Absorbed = FMath::Min(DamageAmount, Equivalent);
	const float Amount = Absorbed * DamageType->MiningPower;

	// Whole number part is guaranteed
	const int Guaranteed = FMath::FloorToInt(Amount);
	for(int Number = 0; Number < Guaranteed; Number++)
	{
		CreatePod();
	}

	// Fractional part used as probability
	const float Rand = FMath::RandRange(0, 1);
	if(Rand <= FMath::Frac(Amount))
	{
		CreatePod();
	}

	return Absorbed;
}

void AAsteroid::CreatePod()
{
	GUARD(DepletedAmount < MaxAmount);
	DepletedAmount++;

	FActorSpawnParameters Parameters;
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AItemPod* Pod = GetWorld()->SpawnActor<AItemPod>(PodClass, GetActorLocation(), GetActorRotation(), Parameters);
	Pod->Init(Composition, 1);
}
