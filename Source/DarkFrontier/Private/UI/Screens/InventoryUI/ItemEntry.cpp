// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/InventoryUI/ItemEntry.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "Components/ListViewBase.h"
#include "Items/Inventory.h"
#include "Items/Item.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"
#include "UI/Screens/InventoryUI/InventoryUI.h"
#include "UI/Screens/InventoryUI/ItemEntryObject.h"
#include "UI/Screens/InventoryUI/ItemList.h"

void UItemEntry::NativeConstruct()
{
	Super::NativeConstruct();

	SelectButton->OnClicked().AddUObject<UItemEntry>(this, &UItemEntry::OnSelected);
}

void UItemEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UItemEntryObject* Object = Cast<UItemEntryObject>(ListItemObject);

	Inventory = Object->Inventory;
	Item = Object->Item;

	IconImage->SetBrushFromTexture(Item->Icon);
	NameText->SetText(Item->Name);

	UpdateQuantity(Item, Inventory->GetItemQuantity(Item));

	Inventory->OnItemChanged.AddUObject<UItemEntry>(this, &UItemEntry::UpdateQuantity);
}

void UItemEntry::NativeOnEntryReleased()
{
	IUserObjectListEntry::NativeOnEntryReleased();

	Inventory->OnItemChanged.RemoveAll(this);
}

void UItemEntry::OnSelected()
{
	UItemList* List = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UItemList>(GetOwningListView());
	List->SetSelectedItem(Item);
}

void UItemEntry::UpdateQuantity(UItem* InItem, int InQuantity)
{
	if(Item == InItem)
	{
		QuantityText->SetText(FText::FromString(FString::Printf(TEXT("%d"), InQuantity)));
	}
}
