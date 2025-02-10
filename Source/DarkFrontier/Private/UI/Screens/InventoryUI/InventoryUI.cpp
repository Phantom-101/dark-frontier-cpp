// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/InventoryUI/InventoryUI.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "Factions/Faction.h"
#include "Items/Inventory.h"
#include "Items/Item.h"
#include "Items/ItemStack.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"
#include "Structures/Structure.h"
#include "Structures/StructureLocation.h"
#include "UI/Screens/UIBase.h"
#include "UI/Screens/InventoryUI/InventoryDisposeModal.h"
#include "UI/Screens/InventoryUI/InventoryOption.h"
#include "UI/Screens/InventoryUI/InventoryTradeModal.h"
#include "UI/Screens/InventoryUI/InventoryTransferModal.h"
#include "UI/Screens/InventoryUI/ItemList.h"
#include "UI/Widgets/Modals/ListBoxModal.h"
#include "UI/Widgets/Visuals/InfoField.h"

void UInventoryUI::NativeConstruct()
{
	Super::NativeConstruct();

	SwitchButton->OnClicked().Clear();
	SwitchButton->OnClicked().AddUObject<UInventoryUI>(this, &UInventoryUI::HandleSwitch);
	TradeButton->OnClicked().Clear();
	TradeButton->OnClicked().AddUObject<UInventoryUI>(this, &UInventoryUI::HandleTrade);
	TransferButton->OnClicked().Clear();
	TransferButton->OnClicked().AddUObject<UInventoryUI>(this, &UInventoryUI::HandleTransfer);
	DisposeButton->OnClicked().Clear();
	DisposeButton->OnClicked().AddUObject<UInventoryUI>(this, &UInventoryUI::HandleDispose);
}

void UInventoryUI::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UInventory* Inventory = GetCurrentInventory();
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
		VolumeField->SetContentFromFloat(Inventory->GetItemVolume(Selected));
		MassField->SetContentFromFloat(Inventory->GetItemMass(Selected));
	}
}

TOptional<FUIInputConfig> UInventoryUI::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture);
}

void UInventoryUI::SetCurrentStructure(AStructure* InStructure)
{
	CurrentStructure = InStructure;
	ItemList->SetInventory(CurrentStructure->GetInventory());
}

AStructure* UInventoryUI::GetCurrentStructure() const
{
	return CurrentStructure;
}

UInventory* UInventoryUI::GetCurrentInventory() const
{
	return ItemList->GetInventory();
}

void UInventoryUI::HandleSwitch()
{
	const UUIBase* Base = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UUIBase>(this);

	if(IsValid(CurrentModal))
	{
		CurrentModal->DeactivateWidget();
		CurrentModal = nullptr;
	}

	UListBoxModal* SwitchModal = Base->PushModal<UListBoxModal>(ListBoxModalClass);
	SwitchModal->SetOptionsWithInitial(TArray<UObject*>(CurrentStructure->GetLocation()->GetInTree()), CurrentStructure);
	SwitchModal->SetBuilder([Owner = SwitchModal, Class = InventoryOptionClass](UObject* Structure)
	{
		UInventoryOption* Option = CreateWidget<UInventoryOption>(Owner, Class);
		Option->Init(Cast<AStructure>(Structure));
		return Option;
	});

	SwitchModal->OnConfirmed.Clear();
	SwitchModal->OnConfirmed.AddUObject<UInventoryUI>(this, &UInventoryUI::HandleSwitchConfirmed);
	CurrentModal = SwitchModal;
}

void UInventoryUI::HandleSwitchConfirmed(UObject* Selection)
{
	SetCurrentStructure(Cast<AStructure>(Selection));
}

void UInventoryUI::HandleTrade()
{
	const UUIBase* Base = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UUIBase>(this);

	if(IsValid(CurrentModal))
	{
		CurrentModal->DeactivateWidget();
		CurrentModal = nullptr;
	}

	TArray<AStructure*> Targets = CurrentStructure->GetLocation()->GetInTree();
	const AFaction* CurrentFaction = CurrentStructure->GetOwningFaction();
	int Index = 0;
	while(Index < Targets.Num())
	{
		if(Targets[Index]->GetOwningFaction() == CurrentFaction)
		{
			Targets.RemoveAt(Index);
		}
		else
		{
			Index++;
		}
	}
	
	UInventoryTradeModal* TradeModal = Base->PushModal<UInventoryTradeModal>(TradeModalClass);
	TradeModal->Init(ItemList->GetInventory(), ItemList->GetSelectedItem(), Targets);

	TradeModal->OnConfirmed.Clear();
	TradeModal->OnConfirmed.AddUObject<UInventoryUI>(this, &UInventoryUI::HandleTradeConfirmed);

	CurrentModal = TradeModal;
}

void UInventoryUI::HandleTradeConfirmed(const FItemStack Trade, AStructure* Target) const
{
	if(Trade.Quantity > 0)
	{
		ItemList->GetInventory()->AddItems(Trade.Item, Trade.Quantity);
		Target->GetInventory()->RemoveItems(Trade.Item, Trade.Quantity);
	}
	else
	{
		ItemList->GetInventory()->RemoveItems(Trade.Item, Trade.Quantity);
		Target->GetInventory()->AddItems(Trade.Item, Trade.Quantity);
	}
	ItemList->GetInventory()->GetStructure()->GetOwningFaction()->ChangeWealth(-Trade.Quantity * Trade.Item->Value);
	Target->GetOwningFaction()->ChangeWealth(Trade.Quantity * Trade.Item->Value);
}

void UInventoryUI::HandleTransfer()
{
	const UUIBase* Base = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UUIBase>(this);

	if(IsValid(CurrentModal))
	{
		CurrentModal->DeactivateWidget();
		CurrentModal = nullptr;
	}

	TArray<AStructure*> Targets = CurrentStructure->GetLocation()->GetInTree();
	Targets.Remove(CurrentStructure);
	
	UInventoryTransferModal* TransferModal = Base->PushModal<UInventoryTransferModal>(TransferModalClass);
	TransferModal->Init(ItemList->GetInventory(), ItemList->GetSelectedItem(), Targets);

	TransferModal->OnConfirmed.Clear();
	TransferModal->OnConfirmed.AddUObject<UInventoryUI>(this, &UInventoryUI::HandleTransferConfirmed);

	CurrentModal = TransferModal;
}

void UInventoryUI::HandleTransferConfirmed(const FItemStack Transfer, AStructure* Target) const
{
	ItemList->GetInventory()->RemoveItems(Transfer.Item, Transfer.Quantity);
	Target->GetInventory()->AddItems(Transfer.Item, Transfer.Quantity);
}

void UInventoryUI::HandleDispose()
{
	const UUIBase* Base = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UUIBase>(this);

	if(IsValid(CurrentModal))
	{
		CurrentModal->DeactivateWidget();
		CurrentModal = nullptr;
	}
	
	UInventoryDisposeModal* DisposeModal = Base->PushModal<UInventoryDisposeModal>(DisposeModalClass);
	DisposeModal->Init(ItemList->GetInventory(), ItemList->GetSelectedItem());

	DisposeModal->OnConfirmed.Clear();
	DisposeModal->OnConfirmed.AddUObject<UInventoryUI>(this, &UInventoryUI::HandleDisposeConfirmed);

	CurrentModal = DisposeModal;
}

void UInventoryUI::HandleDisposeConfirmed(const FItemStack Dispose) const
{
	ItemList->GetInventory()->RemoveItems(Dispose.Item, Dispose.Quantity);
}
