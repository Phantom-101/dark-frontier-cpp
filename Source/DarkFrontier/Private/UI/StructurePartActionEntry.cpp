// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/StructurePartActionEntry.h"

#include "CommonButtonBase.h"
#include "Structures/StructurePartAction.h"

void UStructurePartActionEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	Action = Cast<UStructurePartAction>(ListItemObject);

	ActionButton->OnClicked().AddUObject<UStructurePartActionEntry>(this, &UStructurePartActionEntry::OnActionButtonClicked);
}

void UStructurePartActionEntry::OnActionButtonClicked() const
{
	Action->Trigger();
}
