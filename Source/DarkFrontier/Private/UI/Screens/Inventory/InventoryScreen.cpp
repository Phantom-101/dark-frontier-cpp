// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Inventory/InventoryScreen.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "Components/WidgetSwitcher.h"
#include "Factions/Faction.h"
#include "Items/Item.h"
#include "Libraries/StructureFunctionLibrary.h"
#include "Libraries/UIFunctionLibrary.h"
#include "Structures/Structure.h"
#include "Structures/StructureInventory.h"
#include "UI/Screens/Screens.h"
#include "UI/Screens/Inventory/InventoryDisposeModal.h"
#include "UI/Screens/Inventory/InventoryEntry.h"
#include "UI/Screens/Inventory/InventoryItem.h"
#include "UI/Screens/Inventory/InventoryTradeModal.h"
#include "UI/Screens/Inventory/InventoryTransferModal.h"
#include "UI/Widgets/Modals/ListBoxModal.h"
#include "UI/Widgets/Visuals/InfoField.h"

void UInventoryScreen::NativeConstruct()
{
	Super::NativeConstruct();

	SwitchButton->OnClicked().AddUObject<UInventoryScreen>(this, &UInventoryScreen::HandleSwitch);
	TradeButton->OnClicked().AddUObject<UInventoryScreen>(this, &UInventoryScreen::HandleTrade);
	TransferButton->OnClicked().AddUObject<UInventoryScreen>(this, &UInventoryScreen::HandleTransfer);
	DisposeButton->OnClicked().AddUObject<UInventoryScreen>(this, &UInventoryScreen::HandleDispose);
}

void UInventoryScreen::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	const UInventory* Inventory = GetInventory();
	const UInventoryItem* Selected = ListView->GetSelectedItem<UInventoryItem>();
	if(Selected == nullptr)
	{
		InfoSwitcher->SetActiveWidget(NoItem);
	}
	else
	{
		InfoSwitcher->SetActiveWidget(ItemInfo);

		IconImage->SetBrushFromTexture(Selected->Item->Icon);
		NameText->SetText(Selected->Item->Name);
		DescriptionText->SetText(Selected->Item->Description);
		QuantityField->SetContentFromInt(Inventory->GetQuantity(Selected->Item));
		VolumeField->SetContentFromFloat(Inventory->GetVolume(Selected->Item));
		MassField->SetContentFromFloat(Inventory->GetMass(Selected->Item));
	}
}

TOptional<FUIInputConfig> UInventoryScreen::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture);
}

void UInventoryScreen::SetStructure(AStructure* InStructure)
{
	if(IsValid(Structure))
	{
		GetInventory()->OnChanged.RemoveAll(this);
	}
	
	Structure = InStructure;

	if(IsValid(Structure))
	{
		GetInventory()->OnChanged.AddUObject<UInventoryScreen>(this, &UInventoryScreen::Rebuild);
	}
	
	Rebuild();
}

AStructure* UInventoryScreen::GetStructure() const
{
	return Structure;
}

UStructureInventory* UInventoryScreen::GetInventory() const
{
	return Structure->GetInventory();
}

void UInventoryScreen::Rebuild() const
{
	const UInventoryItem* Selected = ListView->GetSelectedItem<UInventoryItem>();

	ListView->ClearListItems();
	for(UItem* Item : GetInventory()->GetItems())
	{
		UInventoryItem* InventoryItem = UInventoryItem::New(GetInventory(), Item);
		ListView->AddItem(InventoryItem);

		if(IsValid(Selected) && Item == Selected->Item)
		{
			ListView->SetSelectedItem(InventoryItem);
		}
	}
	ListView->RegenerateAllEntries();
}

void UInventoryScreen::HandleSwitch()
{
	const UScreens* Screens = UUIFunctionLibrary::GetParentWidgetOfClass<UScreens>(this);

	if(IsValid(CurrentModal))
	{
		CurrentModal->DeactivateWidget();
		CurrentModal = nullptr;
	}

	UListBoxModal* SwitchModal = Screens->GetStack()->AddWidget<UListBoxModal>(ListBoxModalClass);
	SwitchModal->SetOptionsWithInitial(TArray<UObject*>(UStructureFunctionLibrary::GetInTree(Structure)), Structure);
	SwitchModal->SetBuilder([Owner = SwitchModal, Class = InventoryEntryClass](UObject* Structure)
	{
		UInventoryEntry* Option = CreateWidget<UInventoryEntry>(Owner, Class);
		Option->Init(Cast<AStructure>(Structure));
		return Option;
	});

	SwitchModal->OnConfirmed.Clear();
	SwitchModal->OnConfirmed.AddUObject<UInventoryScreen>(this, &UInventoryScreen::HandleSwitchConfirmed);
	CurrentModal = SwitchModal;
}

void UInventoryScreen::HandleSwitchConfirmed(UObject* Selection)
{
	SetStructure(Cast<AStructure>(Selection));
}

void UInventoryScreen::HandleTrade()
{
	const UScreens* Screens = UUIFunctionLibrary::GetParentWidgetOfClass<UScreens>(this);

	if(IsValid(CurrentModal))
	{
		CurrentModal->DeactivateWidget();
		CurrentModal = nullptr;
	}

	TArray<AStructure*> Targets = UStructureFunctionLibrary::GetInTree(Structure);
	const AFaction* CurrentFaction = Structure->GetAffiliation()->GetFaction();
	int Index = 0;
	while(Index < Targets.Num())
	{
		if(Targets[Index]->GetAffiliation()->GetFaction() == CurrentFaction)
		{
			Targets.RemoveAt(Index);
		}
		else
		{
			Index++;
		}
	}
	
	UInventoryTradeModal* TradeModal = Screens->GetStack()->AddWidget<UInventoryTradeModal>(TradeModalClass);
	TradeModal->Init(GetInventory(), ListView->GetSelectedItem<UInventoryItem>()->Item, Targets);

	CurrentModal = TradeModal;
}

void UInventoryScreen::HandleTransfer()
{
	const UScreens* Screens = UUIFunctionLibrary::GetParentWidgetOfClass<UScreens>(this);

	if(IsValid(CurrentModal))
	{
		CurrentModal->DeactivateWidget();
		CurrentModal = nullptr;
	}

	TArray<AStructure*> Targets = UStructureFunctionLibrary::GetInTree(Structure);
	Targets.Remove(Structure);
	
	UInventoryTransferModal* TransferModal = Screens->GetStack()->AddWidget<UInventoryTransferModal>(TransferModalClass);
	TransferModal->Init(GetInventory(), ListView->GetSelectedItem<UInventoryItem>()->Item, Targets);

	CurrentModal = TransferModal;
}

void UInventoryScreen::HandleDispose()
{
	const UScreens* Screens = UUIFunctionLibrary::GetParentWidgetOfClass<UScreens>(this);

	if(IsValid(CurrentModal))
	{
		CurrentModal->DeactivateWidget();
		CurrentModal = nullptr;
	}
	
	UInventoryDisposeModal* DisposeModal = Screens->GetStack()->AddWidget<UInventoryDisposeModal>(DisposeModalClass);
	DisposeModal->Init(GetInventory(), ListView->GetSelectedItem<UInventoryItem>()->Item);

	CurrentModal = DisposeModal;
}
