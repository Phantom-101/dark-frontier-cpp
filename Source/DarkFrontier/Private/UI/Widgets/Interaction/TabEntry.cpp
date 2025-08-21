// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Interaction/TabEntry.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "UI/Widgets/Interaction/Tabs.h"

void UTabEntry::Init(UTab* InTab)
{
	Tab = InTab;
	IconImage->SetBrushFromTexture(InTab->Icon);
	NameText->SetText(InTab->Name);
}

void UTabEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	USelectableEntry::NativeOnListItemObjectSet(ListItemObject);
	Init(Cast<UTab>(ListItemObject));
}
