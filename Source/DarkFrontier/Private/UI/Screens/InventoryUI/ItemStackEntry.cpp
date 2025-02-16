// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/InventoryUI/ItemStackEntry.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "Components/ListViewBase.h"
#include "Items/Inventory.h"
#include "Items/Item.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"
#include "UI/Screens/InventoryUI/ItemEntryObject.h"
#include "UI/Screens/InventoryUI/ItemList.h"

void UItemStackEntry::NativeConstruct()
{
	Super::NativeConstruct();

	SelectButton->OnClicked().AddUObject<UItemStackEntry>(this, &UItemStackEntry::OnSelected);
}

void UItemStackEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UItemEntryObject* Object = Cast<UItemEntryObject>(ListItemObject);

	Inventory = Object->Inventory;
	Item = Object->Item;

	IconImage->SetBrushFromTexture(Item->Icon);
	NameText->SetText(Item->Name);

	UpdateQuantity(Item, Inventory->GetItemQuantity(Item));

	Inventory->OnItemChanged.AddUObject<UItemStackEntry>(this, &UItemStackEntry::UpdateQuantity);
}

void UItemStackEntry::NativeOnEntryReleased()
{
	IUserObjectListEntry::NativeOnEntryReleased();

	Inventory->OnItemChanged.RemoveAll(this);
}

void UItemStackEntry::OnSelected() const
{
	UItemList* List = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UItemList>(GetOwningListView());
	List->SetSelectedItem(Item);
}

void UItemStackEntry::UpdateQuantity(UItem* InItem, int InQuantity) const
{
	if(Item == InItem)
	{
		QuantityText->SetText(FText::FromString(FString::Printf(TEXT("%d"), InQuantity)));
	}
}
