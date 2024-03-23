// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructurePartSlotInfo.h"
#include "CommonTextBlock.h"
#include "Structures/StructurePartSlot.h"
#include "UI/Screens/StructureDetails/StructurePartCard.h"
#include "UI/Screens/StructureDetails/StructurePartSlotCard.h"

void UStructurePartSlotInfo::SetTarget(UStructurePartSlot* InTargetSlot)
{
	TargetSlot = InTargetSlot;

	NameText->SetText(TargetSlot->SlotName);
	PartCard->SetTarget(TargetSlot->OwningPart);
	AttachedSlotCard->SetTarget(TargetSlot->AttachedSlot);
}
