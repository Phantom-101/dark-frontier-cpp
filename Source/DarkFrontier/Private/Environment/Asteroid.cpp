// Fill out your copyright notice in the Description page of Project Settings.

#include "Environment/Asteroid.h"
#include "Log.h"
#include "Macros.h"
#include "Items/Item.h"
#include "Items/ItemPod.h"
#include "Structures/StructureDamageType.h"

AAsteroid::AAsteroid()
{
	Location = CreateDefaultSubobject<USectorLocation>("Location");
	Targetable = CreateDefaultSubobject<UTargetable>("Targetable");
}

const TMap<TObjectPtr<UItem>, float>& AAsteroid::GetComposition() const
{
	return Composition;
}

float AAsteroid::GetMaxWeight() const
{
	return Algo::TransformAccumulate(Composition, [](const TTuple<TObjectPtr<UItem>, float>& Pair)
	{
		return Pair.Value;
	}, 0);
}

int AAsteroid::GetMaxAmount() const
{
	return MaxAmount;
}

int AAsteroid::GetDepletedAmount() const
{
	return DepletedAmount;
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
	const float Amount = Absorbed * DamageType->MiningPower * AmountPerDamage;

	// Whole number part is guaranteed
	const int Guaranteed = FMath::FloorToInt(Amount);
	for(int Number = 0; Number < Guaranteed; Number++)
	{
		CreatePod();
	}

	// Fractional part used as probability
	const float Rand = FMath::RandRange(0.f, 1.f);
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

	UItem* Item = RandomItem();
	GUARD(IsValid(Item));
	
	AItemPod* Pod = GetWorld()->SpawnActor<AItemPod>(PodClass);
	
	USectorLocation* PodLocation = Pod->GetSectorLocation();
	PodLocation->SetSector(GetSectorLocation()->GetSector());
	PodLocation->SetLocation(GetActorLocation());
	
	Pod->Init(Item, 1);
}

UItem* AAsteroid::RandomItem() const
{
	const float TotalWeight = GetMaxWeight();
	GUARD_RETURN(TotalWeight > 0, nullptr);
	const float Rand = FMath::RandRange(0.f, TotalWeight);
	float Threshold = 0;
	for(const TTuple<TObjectPtr<UItem>, float>& Pair : Composition)
	{
		Threshold += Pair.Value;
		if(Rand <= Threshold && Pair.Value != 0)
		{
			return Pair.Key;
		}
	}
	return nullptr;
}
