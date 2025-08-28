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
	return IsValid(Target.GetObject());
}

bool ATractorBeam::CanActivate(const TScriptInterface<ITargetable>& InTarget) const
{
	GUARD_RETURN(IsValid(InTarget.GetObject()), false);
	if(InTarget.GetObject()->IsA<AItemPod>())
	{
		const AItemPod* ItemPod = Cast<AItemPod>(InTarget.GetObject());
		return (ItemPod->GetActorLocation() - GetActorLocation()).SizeSquared() <= TractorRange * TractorRange;
	}
	if(InTarget.GetObject()->IsA<AStructure>())
	{
		const AStructure* Structure = Cast<AStructure>(InTarget.GetObject());
		return (Structure->GetActorLocation() - GetActorLocation()).SizeSquared() <= TractorRange * TractorRange;
	}
	return false;
}

void ATractorBeam::OnActivate(const TScriptInterface<ITargetable>& InTarget)
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

	GUARD(IsValid(Target.GetObject()));
	if(Target.GetObject()->IsA<AItemPod>())
	{
		AItemPod* ItemPod = Cast<AItemPod>(Target.GetObject());
		ItemPod->GetStaticMesh()->AddForce(GetForce(ItemPod->GetActorLocation()));
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
	else if(Target.GetObject()->IsA<AStructure>())
	{
		const AStructure* Structure = Cast<AStructure>(Target.GetObject());
		Structure->GetStaticMesh()->AddForce(GetForce(Structure->GetActorLocation()));
	}
}

FVector ATractorBeam::GetForce(const FVector& TargetLocation) const
{
	FVector Force = GetActorLocation() - TargetLocation;
	Force.Normalize();
	Force *= TractorForce;
	return Force;
}
