// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructurePartSlot.h"
#include "Structures/Structure.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartSlotType.h"
#include "Kismet/KismetMathLibrary.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

UStructurePartSlot::UStructurePartSlot()
{
}

void UStructurePartSlot::BeginPlay()
{
	Super::BeginPlay();

	OwningPart = Cast<AStructurePart>(GetOwner());
	OwningPart->RegisterPartSlot(this);
}

void UStructurePartSlot::Attach(UStructurePartSlot* NewSlot)
{
	if(NewSlot == nullptr)
	{
		Detach();
		return;
	}

	if(AttachedSlot == nullptr && NewSlot->AttachedSlot == nullptr && SlotType.GetDefaultObject()->CanAttach(NewSlot->SlotType.GetDefaultObject()))
	{
		if(OwningPart->OwningStructure == nullptr)
		{
			// Part previously not attached
			AttachedSlot = NewSlot;
			AttachedSlot->AttachedSlot = this;
			OwningPart->InitOwningStructure(AttachedSlot->OwningPart->OwningStructure);
			MatchTransform(AttachedSlot);
			OwningPart->AttachNearbyPartSlots();
		}
		else if (OwningPart->OwningStructure == NewSlot->OwningPart->OwningStructure)
		{
			// Part already attached, simply connecting all nearby slots
			AttachedSlot = NewSlot;
			NewSlot->AttachedSlot = this;
		}
		OwningPart->OwningStructure->UpdatePartDistances();
	}
}

void UStructurePartSlot::Detach()
{
	if (AttachedSlot != nullptr)
	{
		AttachedSlot->AttachedSlot = nullptr;
		AttachedSlot = nullptr;
		OwningPart->OwningStructure->UpdateCachedParts();
		OwningPart->OwningStructure->UpdatePartDistances();
	}
}

void UStructurePartSlot::MatchTransform(UStructurePartSlot* Other)
{
	// Match part xy with other slot xy
	OwningPart->SetActorRotation(UKismetMathLibrary::MakeRotFromXY(-Other->GetForwardVector(), Other->GetRightVector()));
	// Match current slot xy with other slot xy
	OwningPart->AddActorLocalRotation(OwningPart->GetTransform().InverseTransformRotation(GetComponentRotation().Quaternion()).Rotator().GetInverse());
	// Match current slot position with other slot position
	const FVector Offset = GetComponentLocation() - OwningPart->GetActorLocation();
	OwningPart->SetActorLocation(Other->GetComponentLocation() - Offset);
}

void UStructurePartSlot::PhysicallyAttach(UStructurePartSlot* NewSlot)
{
	UPhysicsConstraintComponent* Constraint = NewObject<UPhysicsConstraintComponent>(this);

	Constraint->OverrideComponent1 = Cast<UStaticMeshComponent>(OwningPart->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	Constraint->OverrideComponent2 = Cast<UStaticMeshComponent>(NewSlot->OwningPart->GetComponentByClass(UStaticMeshComponent::StaticClass()));

	Constraint->SetAngularSwing1Limit(ACM_Locked, 0);
	Constraint->SetAngularSwing2Limit(ACM_Locked, 0);
	Constraint->SetAngularTwistLimit(ACM_Locked, 0);
	Constraint->SetDisableCollision(true);

	Constraint->RegisterComponent();
}
