// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/InventoryUI/InventoryOption.h"
#include "CommonTextBlock.h"
#include "Structures/Structure.h"

void UInventoryOption::Init(const AStructure* Structure) const
{
	NameText->SetText(FText::FromString(Structure->GetName()));
}
