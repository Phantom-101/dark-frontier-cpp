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
	
	OwningPart = GetOwner<AStructurePart>();
}

FText UStructurePartSlot::GetSlotName() const
{
	return SlotName;
}

UStructurePartSlotType* UStructurePartSlot::GetSlotType() const
{
	return SlotType;
}

AStructure* UStructurePartSlot::GetOwningStructure() const
{
	checkf(OwningPart != nullptr, TEXT("Owning part should not be null"));
	return OwningPart->GetOwningStructure();
}

AStructurePart* UStructurePartSlot::GetOwningPart() const
{
	return OwningPart;
}

UStructurePartSlot* UStructurePartSlot::GetAttachedSlot() const
{
	return AttachedSlot;
}

bool UStructurePartSlot::CanAttach(const UStructurePartSlot* Other) const
{
	return Filter->IsCompatible(Other) && Other->Filter->IsCompatible(this);
}

bool UStructurePartSlot::TryAttach(UStructurePartSlot* NewSlot)
{
	if(NewSlot == nullptr) return false; // New slot must be non-null
	if(AttachedSlot != nullptr || NewSlot->AttachedSlot != nullptr) return false; // Both slots must be detached
	if(GetOwningStructure() == nullptr && NewSlot->GetOwningStructure() == nullptr) return false; // At least one slot must be part of an existing structure
	if(!CanAttach(NewSlot)) return false;

	AttachedSlot = NewSlot;
	AttachedSlot->AttachedSlot = this;

	MatchTransform(AttachedSlot);
	
	if(GetOwningStructure() == nullptr)
	{
		// This part previously not attached
		OwningPart->TryInit(AttachedSlot->GetOwningStructure());
		OwningPart->AttachSlots();
	}
	else if(AttachedSlot->GetOwningStructure() == nullptr)
	{
		// Other part previously not attached
		AttachedSlot->OwningPart->TryInit(GetOwningStructure());
		AttachedSlot->OwningPart->AttachSlots();
	}
	
	GetOwningStructure()->UpdateLayoutInformation();
	return true;
}

bool UStructurePartSlot::TryDetach()
{
	if(AttachedSlot == nullptr) return true; // Slot already detached
	
	AttachedSlot->AttachedSlot = nullptr;
	AttachedSlot = nullptr;
	GetOwningStructure()->UpdateLayoutInformation();

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
