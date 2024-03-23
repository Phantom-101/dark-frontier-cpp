// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructurePartSlot.h"
#include "Structures/StructurePart.h"
#include "Kismet/KismetMathLibrary.h"
#include "Structures/Structure.h"
#include "Structures/StructurePartSlotFilter.h"

UStructurePartSlot::UStructurePartSlot()
{
	Filter = CreateDefaultSubobject<UStructurePartSlotFilter>("Filter");
}

void UStructurePartSlot::BeginPlay()
{
	Super::BeginPlay();

	OwningPart = Cast<AStructurePart>(GetOwner());
	OwningPart->RegisterPartSlot(this);
}

bool UStructurePartSlot::CanAttach(const UStructurePartSlot* Other) const
{
	return Filter->IsCompatible(Other) && Other->Filter->IsCompatible(this);
}

void UStructurePartSlot::Attach(UStructurePartSlot* NewSlot)
{
	if(NewSlot == nullptr)
	{
		Detach();
		return;
	}

	if(AttachedSlot == nullptr && NewSlot->AttachedSlot == nullptr && CanAttach(NewSlot))
	{
		AttachedSlot = NewSlot;
		AttachedSlot->AttachedSlot = this;
		
		if(OwningPart->OwningStructure == nullptr)
		{
			// This part previously not attached
			OwningPart->InitOwningStructure(AttachedSlot->OwningPart->OwningStructure);
			MatchTransform(AttachedSlot);
			OwningPart->AttachNearbyPartSlots();
		}
		else if(AttachedSlot->OwningPart->OwningStructure == nullptr)
		{
			// Other part previously not attached
			AttachedSlot->OwningPart->InitOwningStructure(OwningPart->OwningStructure);
			AttachedSlot->MatchTransform(this);
			AttachedSlot->OwningPart->AttachNearbyPartSlots();
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
