// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/TractorBeam.h"
#include "Macros.h"
#include "Items/ItemPod.h"
#include "Libraries/BoundsFunctionLibrary.h"
#include "Structures/Structure.h"
#include "Structures/StructureInventory.h"

ATractorBeam::ATractorBeam()
{
	PrimaryActorTick.bCanEverTick = true;
}

bool ATractorBeam::IsActivated() const
{
	return IsValid(Target);
}

bool ATractorBeam::CanActivate(UTargetable* InTarget) const
{
	GUARD_RETURN(IsValid(InTarget), false);
	const AActor* TargetActor = InTarget->GetOwner();
	GUARD_RETURN(TargetActor->IsA<AItemPod>() || TargetActor->IsA<AStructure>(), false);
	return (TargetActor->GetActorLocation() - GetActorLocation()).SizeSquared() <= TractorRange * TractorRange;
}

void ATractorBeam::OnActivate(UTargetable* InTarget)
{
	Target = InTarget;
}

bool ATractorBeam::CanDeactivate() const
{
	return IsActivated();
}

void ATractorBeam::TryDeactivate()
{
	Target = nullptr;
}

void ATractorBeam::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	GUARD(IsValid(Target));
	if(Target->GetOwner()->IsA<AItemPod>())
	{
		AItemPod* ItemPod = Target->GetOwner<AItemPod>();
		ItemPod->GetStaticMesh()->AddForce(GetForce());
		const FVector Delta = GetActorLocation() - ItemPod->GetActorLocation();
		const float Radius = UBoundsFunctionLibrary::GetLocalBounds(GetOwningStructure(), true).SphereRadius;
		const float FinalRange = Radius + CollectionRange;
		if(Delta.SizeSquared() <= FinalRange * FinalRange)
		{
			ItemPod->AddToInventory(GetOwningStructure()->GetInventory());
			Target = nullptr;
			// May need to add overlap check in case this does not fully work
		}
	}
	else if(Target->GetOwner()->IsA<AStructure>())
	{
		const AStructure* Structure = Target->GetOwner<AStructure>();
		Structure->GetStaticMesh()->AddForce(GetForce());
	}
}

FVector ATractorBeam::GetForce() const
{
	FVector Force = GetActorLocation() - Target->GetOwner()->GetActorLocation();
	Force.Normalize();
	Force *= TractorForce;
	return Force;
}
