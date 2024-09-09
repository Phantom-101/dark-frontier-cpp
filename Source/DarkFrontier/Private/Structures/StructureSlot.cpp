// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureSlot.h"
#include "Log.h"
#include "Structures/StructurePart.h"
#include "Structures/Structure.h"
#include "Kismet/KismetMathLibrary.h"
#include "Structures/StructureIndices.h"
#include "Structures/StructurePartFilter.h"

UStructureSlot::UStructureSlot()
{
	Filter = CreateDefaultSubobject<UStructurePartFilter>("Filter");
}

void UStructureSlot::BeginPlay()
{
	Super::BeginPlay();
	
	OwningPart = GetOwner<AStructurePart>();
}

FText UStructureSlot::GetSlotName() const
{
	return SlotName;
}

AStructure* UStructureSlot::GetOwningStructure() const
{
	if(!IsValid(OwningPart)) return nullptr;
	return OwningPart->GetOwningStructure();
}

AStructurePart* UStructureSlot::GetOwningPart() const
{
	return OwningPart;
}

const AStructurePart* UStructureSlot::GetOwningPart_Always() const
{
	if(IsValid(OwningPart))
	{
		return OwningPart;
	}

	return GetOwningPart_CDO(this);
}

UStructureSlot* UStructureSlot::GetAttachedSlot() const
{
	return AttachedSlot;
}

bool UStructureSlot::CanAttach(const UStructureSlot* Other) const
{
	return Filter->IsCompatible(Other->GetOwningPart_Always()) && Other->Filter->IsCompatible(GetOwningPart_Always());
}

/**
 * @note If both slots are already part of layout, the new slot will be moved with reference to the callee slot. This is not necessary when attaching nearby slots but required when loading from a layout object as parts were created without any prior connections/physical adjustments.
 */
bool UStructureSlot::TryAttach(UStructureSlot* NewSlot, bool SuppressUpdate)
{
	if(!IsValid(NewSlot))
	{
		UE_LOG(LogDarkFrontier, Warning, TEXT("New slot must be valid"));
		return false;
	}
	
	if(AttachedSlot || NewSlot->AttachedSlot)
	{
		UE_LOG(LogDarkFrontier, Warning, TEXT("Both slots must be null for them to attach"));
		return false;
	}
	
	if(!IsValid(GetOwningStructure()) && !IsValid(NewSlot->GetOwningStructure()))
	{
		UE_LOG(LogDarkFrontier, Warning, TEXT("Neither slot has valid owning structure"));
		return false;
	}

	if((GetOwningStructure() && !IsValid(GetOwningStructure())) ||
		(NewSlot->GetOwningStructure() && !IsValid(NewSlot->GetOwningStructure())))
	{
		UE_LOG(LogDarkFrontier, Warning, TEXT("Cannot attach slot with non-valid owning structure"));
		return false;
	}
	
	if(!CanAttach(NewSlot))
	{
		UE_LOG(LogDarkFrontier, Warning, TEXT("Slots are not compatible"));
		return false;
	}

	AttachedSlot = NewSlot;
	AttachedSlot->AttachedSlot = this;

	if(!GetOwningStructure())
	{
		// This part previously not attached
		AttachedSlot->GetOwningStructure()->GetIndices()->AddPart(OwningPart);
		MatchTransform(AttachedSlot);
		OwningPart->AttachSlots();
	}
	else if(!AttachedSlot->GetOwningStructure())
	{
		// Other part previously not attached
		GetOwningStructure()->GetIndices()->AddPart(AttachedSlot->OwningPart);
		AttachedSlot->MatchTransform(this);
		AttachedSlot->OwningPart->AttachSlots();
	}
	else
	{
		// Use other slot as reference
		AttachedSlot->MatchTransform(this);
		AttachedSlot->OwningPart->AttachSlots();
	}

	if(!SuppressUpdate)
	{
		GetOwningStructure()->UpdateLayoutInformation();
	}
	
	return true;
}

bool UStructureSlot::TryDetach()
{
	if(!AttachedSlot) return true; // Slot already detached
	
	AttachedSlot->AttachedSlot = nullptr;
	AttachedSlot = nullptr;
	GetOwningStructure()->UpdateLayoutInformation();

	return true;
}

void UStructureSlot::MatchTransform(UStructureSlot* Other)
{
	// Match part xy with other slot xy
	OwningPart->SetActorRotation(UKismetMathLibrary::MakeRotFromXY(-Other->GetForwardVector(), -Other->GetRightVector()));
	// Match current slot xy with other slot xy
	OwningPart->AddActorLocalRotation(OwningPart->GetTransform().InverseTransformRotation(GetComponentRotation().Quaternion()).Rotator().GetInverse());
	// Match current slot position with other slot position
	const FVector Offset = GetComponentLocation() - OwningPart->GetActorLocation();
	OwningPart->SetActorLocation(Other->GetComponentLocation() - Offset);
}

const AStructurePart* UStructureSlot::GetOwningPart_CDO(const UStructureSlot* Slot)
{
	const UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(Slot->GetOuter());
	if(BPClass == nullptr) return nullptr;

	return BPClass->GetDefaultObject<AStructurePart>();
}
