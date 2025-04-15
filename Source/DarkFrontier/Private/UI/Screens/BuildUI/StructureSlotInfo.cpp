// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/BuildUI/StructureSlotInfo.h"
#include "CommonTextBlock.h"
#include "Structures/StructureSlot.h"
#include "UI/Screens/BuildUI/StructurePartCard.h"
#include "UI/Screens/BuildUI/StructureSlotCard.h"

UStructureSlot* UStructureSlotInfo::GetTarget() const
{
	return TargetSlot;
}

void UStructureSlotInfo::SetTarget(UStructureSlot* InTargetSlot)
{
	TargetSlot = InTargetSlot;

	NameText->SetText(TargetSlot->GetSlotName());
	PartCard->SetTarget(TargetSlot->GetOwningPart());
	AttachedSlotCard->SetTarget(TargetSlot->GetAttachedSlot());
}
