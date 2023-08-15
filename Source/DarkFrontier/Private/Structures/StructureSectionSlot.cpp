// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureSectionSlot.h"
#include "Structures/Structure.h"
#include "Structures/StructureSection.h"
#include "Structures/StructureSectionSlotType.h"
#include "Kismet/KismetMathLibrary.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

UStructureSectionSlot::UStructureSectionSlot()
{
}

void UStructureSectionSlot::BeginPlay()
{
	Super::BeginPlay();

	OwningSection = Cast<AStructureSection>(GetOwner());
	OwningSection->RegisterSectionSlot(this);
}

void UStructureSectionSlot::Attach(UStructureSectionSlot* NewSlot)
{
	if(AttachedSlot == nullptr && NewSlot->AttachedSlot == nullptr && SlotType.GetDefaultObject()->CanAttach(NewSlot->SlotType.GetDefaultObject()))
	{
		if(OwningSection->OwningStructure == nullptr)
		{
			// Section previously not attached
			AttachedSlot = NewSlot;
			NewSlot->AttachedSlot = this;
			OwningSection->InitOwningStructure(AttachedSlot->OwningSection->OwningStructure);
			MatchTransform(AttachedSlot);
			OwningSection->AttachNearbySectionSlots();
		}
		else if (OwningSection->OwningStructure == NewSlot->OwningSection->OwningStructure)
		{
			// Section already attached, simply connecting all nearby slots
			AttachedSlot = NewSlot;
			NewSlot->AttachedSlot = this;
		}
	}
}

void UStructureSectionSlot::Detach()
{
	if (AttachedSlot != nullptr)
	{
		AttachedSlot->AttachedSlot = nullptr;
		AttachedSlot = nullptr;
		OwningSection->OwningStructure->UpdateSections();
	}
}

void UStructureSectionSlot::MatchTransform(UStructureSectionSlot* Other)
{
	// Match section xy with other slot xy
	OwningSection->SetActorRotation(UKismetMathLibrary::MakeRotFromXY(-Other->GetForwardVector(), Other->GetRightVector()));
	// Match current slot xy with other slot xy
	OwningSection->AddActorLocalRotation(OwningSection->GetTransform().InverseTransformRotation(GetComponentRotation().Quaternion()).Rotator().GetInverse());
	// Match current slot position with other slot position
	const FVector Offset = GetComponentLocation() - OwningSection->GetActorLocation();
	OwningSection->SetActorLocation(Other->GetComponentLocation() - Offset);
}

void UStructureSectionSlot::PhysicallyAttach(UStructureSectionSlot* NewSlot)
{
	UPhysicsConstraintComponent* Constraint = NewObject<UPhysicsConstraintComponent>(this);

	Constraint->OverrideComponent1 = Cast<UStaticMeshComponent>(OwningSection->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	Constraint->OverrideComponent2 = Cast<UStaticMeshComponent>(NewSlot->OwningSection->GetComponentByClass(UStaticMeshComponent::StaticClass()));

	Constraint->SetAngularSwing1Limit(ACM_Locked, 0);
	Constraint->SetAngularSwing2Limit(ACM_Locked, 0);
	Constraint->SetAngularTwistLimit(ACM_Locked, 0);
	Constraint->SetDisableCollision(true);

	Constraint->RegisterComponent();
}
