// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructurePartSlot.h"
#include "Structures/StructurePart.h"
#include "Structures/Structure.h"
#include "Kismet/KismetMathLibrary.h"
#include "Structures/StructurePartSlotFilter.h"

UStructurePartSlot::UStructurePartSlot()
{
	Filter = CreateDefaultSubobject<UStructurePartSlotFilter>("Filter");
}

void UStructurePartSlot::BeginPlay()
{
	Super::BeginPlay();
	
	OwningPart = Cast<AStructurePart>(GetOwner());
}

bool UStructurePartSlot::CanAttach(const UStructurePartSlot* Other) const
{
	return Filter->IsCompatible(Other) && Other->Filter->IsCompatible(this);
}

bool UStructurePartSlot::TryAttach(UStructurePartSlot* NewSlot)
{
	if(NewSlot == nullptr) return false; // New slot must be non-null
	if(AttachedSlot != nullptr || NewSlot->AttachedSlot != nullptr) return false; // Both slots must be detached
	if(OwningPart->OwningStructure == nullptr && NewSlot->OwningPart->OwningStructure == nullptr) return false; // At least one slot must be part of an existing structure
	if(!CanAttach(NewSlot)) return false;

	AttachedSlot = NewSlot;
	AttachedSlot->AttachedSlot = this;

	MatchTransform(AttachedSlot);
	
	if(OwningPart->OwningStructure == nullptr)
	{
		// This part previously not attached
		OwningPart->TryInit(AttachedSlot->OwningPart->OwningStructure);
		OwningPart->AttachSlots();
	}
	else if(AttachedSlot->OwningPart->OwningStructure == nullptr)
	{
		// Other part previously not attached
		AttachedSlot->OwningPart->TryInit(OwningPart->OwningStructure);
		AttachedSlot->OwningPart->AttachSlots();
	}
	
	OwningPart->OwningStructure->UpdateLayoutInformation();
	return true;
}

bool UStructurePartSlot::TryDetach()
{
	if(AttachedSlot == nullptr) return true; // Slot already detached
	
	AttachedSlot->AttachedSlot = nullptr;
	AttachedSlot = nullptr;
	OwningPart->OwningStructure->UpdateLayoutInformation();

	return true;
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
