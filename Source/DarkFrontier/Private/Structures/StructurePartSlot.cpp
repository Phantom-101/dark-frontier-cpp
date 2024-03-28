// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructurePartSlot.h"

#include "Log.h"
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
	if(!IsValid(OwningPart)) return nullptr;
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
	if(!IsValid(NewSlot))
	{
		UE_LOG(LogStructure, Display, TEXT("New slot must be valid"));
		return false;
	}
	
	if(AttachedSlot || NewSlot->AttachedSlot)
	{
		UE_LOG(LogStructure, Display, TEXT("Both slots must be null for them to attach"));
		return false;
	}
	
	if(!IsValid(GetOwningStructure()) && !IsValid(NewSlot->GetOwningStructure()))
	{
		UE_LOG(LogStructure, Display, TEXT("Neither slot has valid owning structure"));
		return false;
	}

	if((GetOwningStructure() && !IsValid(GetOwningStructure())) ||
		(NewSlot->GetOwningStructure() && !IsValid(NewSlot->GetOwningStructure())))
	{
		UE_LOG(LogStructure, Display, TEXT("Cannot attach slot with non-valid owning structure"));
		return false;
	}
	
	if(!CanAttach(NewSlot))
	{
		UE_LOG(LogStructure, Log, TEXT("Slots are not compatible"));
		return false;
	}

	AttachedSlot = NewSlot;
	AttachedSlot->AttachedSlot = this;

	MatchTransform(AttachedSlot);
	
	if(!GetOwningStructure())
	{
		// This part previously not attached
		OwningPart->TryInit(AttachedSlot->GetOwningStructure());
		OwningPart->AttachSlots();
	}
	else if(!AttachedSlot->GetOwningStructure())
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
	if(!AttachedSlot) return true; // Slot already detached
	
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
