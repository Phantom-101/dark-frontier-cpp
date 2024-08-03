// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/InventoryUI/InventoryUI.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "Items/Inventory.h"
#include "Items/Item.h"
#include "UI/Screens/InventoryUI/ItemList.h"
#include "UI/Widgets/InfoField.h"

void UInventoryUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UInventory* Inventory = GetInventory();
	UItem* Selected = ItemList->GetSelectedItem();
	if(Selected == nullptr)
	{
		InfoSwitcher->SetActiveWidget(NoItem);
	}
	else
	{
		InfoSwitcher->SetActiveWidget(ItemInfo);

		IconImage->SetBrushFromTexture(Selected->Icon);
		NameText->SetText(Selected->Name);
		DescriptionText->SetText(Selected->Description);
		QuantityField->SetContentFromInt(Inventory->GetItemQuantity(Selected));
		ValueField->SetContentFromInt(Inventory->GetItemValue(Selected));
		VolumeField->SetContentFromFloat(Inventory->GetItemVolume(Selected));
		MassField->SetContentFromFloat(Inventory->GetItemMass(Selected));
	}
}

TOptional<FUIInputConfig> UInventoryUI::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture);
}

UInventory* UInventoryUI::GetInventory() const
{
	return ItemList->GetInventory();
}

void UInventoryUI::SetInventory(UInventory* InInventory) const
{
	ItemList->SetInventory(InInventory);
}
