// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/StructurePartActionGroupEntry.h"
#include "CommonButtonBase.h"
#include "CommonListView.h"
#include "Libraries/UIBlueprintLibrary.h"
#include "Structures/StructurePartAction.h"
#include "Structures/StructurePartActionGroup.h"
#include "UI/GameUI.h"

void UStructurePartActionGroupEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	ActionGroup = Cast<UStructurePartActionGroup>(ListItemObject);

	GroupButton->OnClicked().AddUObject<UStructurePartActionGroupEntry>(this, &UStructurePartActionGroupEntry::OnGroupButtonClicked);
	UGameUI* GameUI = UUIBlueprintLibrary::GetParentWidgetOfClass<UGameUI>(GetOwningListView());
	GameUI->OnActionsCollapseToggled.RemoveAll(this);
	GameUI->OnActionsCollapseToggled.AddUObject<UStructurePartActionGroupEntry>(this, &UStructurePartActionGroupEntry::OnCollapseToggled);
	OnCollapseToggled(GameUI->GetIsActionsCollapsed());
	
	ActionList->ClearListItems();
	for(UStructurePartAction* Action : ActionGroup->Actions)
	{
		ActionList->AddItem(Action);
	}
	ActionList->RegenerateAllEntries();
	ActionList->ScrollIndexIntoView(0);
}

void UStructurePartActionGroupEntry::OnGroupButtonClicked() const
{
	for(const UStructurePartAction* Action : ActionGroup->Actions)
	{
		Action->Trigger();
	}
}

void UStructurePartActionGroupEntry::OnCollapseToggled(const bool Target) const
{
	ActionList->SetVisibility(Target ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
}
