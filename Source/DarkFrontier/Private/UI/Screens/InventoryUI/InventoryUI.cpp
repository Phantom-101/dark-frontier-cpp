// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/InventoryUI/InventoryUI.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "Factions/Faction.h"
#include "Items/Item.h"
#include "Items/ItemStack.h"
#include "Items/ItemStackObject.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"
#include "Structures/Structure.h"
#include "Structures/StructureInventory.h"
#include "Structures/StructureLocation.h"
#include "UI/Screens/UIBase.h"
#include "UI/Screens/InventoryUI/InventoryDisposeModal.h"
#include "UI/Screens/InventoryUI/InventoryEntry.h"
#include "UI/Screens/InventoryUI/InventoryTradeModal.h"
#include "UI/Screens/InventoryUI/InventoryTransferModal.h"
#include "UI/Screens/InventoryUI/ItemStackEntry.h"
#include "UI/Widgets/Interaction/ListBox.h"
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

	UInventory* Inventory = GetInventory();
	const UItemStackObject* Selected = Cast<UItemStackObject>(ItemListBox->GetCurrentOption());
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

TOptional<FUIInputConfig> UInventoryUI::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture);
}

void UInventoryUI::SetStructure(AStructure* InStructure)
{
	if(IsValid(Structure))
	{
		GetInventory()->OnItemsChanged.RemoveAll(this);
	}
	
	Structure = InStructure;

	if(IsValid(Structure))
	{
		GetInventory()->OnItemsChanged.AddUObject<UInventoryUI>(this, &UInventoryUI::Rebuild);
	}
	
	Rebuild();
}

AStructure* UInventoryUI::GetStructure() const
{
	return Structure;
}

UStructureInventory* UInventoryUI::GetInventory() const
{
	return Structure->GetInventory();
}

void UInventoryUI::Rebuild()
{
	TArray<UObject*> Options;
	UObject* Current = nullptr;
	for(UItem* Item : GetInventory()->GetItems())
	{
		UItemStackObject* Obj = NewObject<UItemStackObject>();
		Obj->Inventory = GetInventory();
		Obj->Item = Item;
		Options.Add(Obj);

		if(ItemListBox->IsCurrentOptionValid() && Item == Cast<UItemStackObject>(ItemListBox->GetCurrentOption())->Item)
		{
			Current = Obj;
		}
	}
	ItemListBox->SetOptionsWithInitial(Options, Current);
	ItemListBox->SetBuilder([Owner = this, Class = ItemStackEntryClass](UObject* ItemStack)
	{
		UItemStackEntry* Option = CreateWidget<UItemStackEntry>(Owner, Class);
		Option->Init(Cast<UItemStackObject>(ItemStack));
		return Option;
	});
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
	SwitchModal->SetOptionsWithInitial(TArray<UObject*>(Structure->GetLocation()->GetInTree()), Structure);
	SwitchModal->SetBuilder([Owner = SwitchModal, Class = InventoryEntryClass](UObject* Structure)
	{
		UInventoryEntry* Option = CreateWidget<UInventoryEntry>(Owner, Class);
		Option->Init(Cast<AStructure>(Structure));
		return Option;
	});

	SwitchModal->OnConfirmed.Clear();
	SwitchModal->OnConfirmed.AddUObject<UInventoryUI>(this, &UInventoryUI::HandleSwitchConfirmed);
	CurrentModal = SwitchModal;
}

void UInventoryUI::HandleSwitchConfirmed(UObject* Selection)
{
	SetStructure(Cast<AStructure>(Selection));
}

void UInventoryUI::HandleTrade()
{
	const UUIBase* Base = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UUIBase>(this);

	if(IsValid(CurrentModal))
	{
		CurrentModal->DeactivateWidget();
		CurrentModal = nullptr;
	}

	TArray<AStructure*> Targets = Structure->GetLocation()->GetInTree();
	const AFaction* CurrentFaction = Structure->GetOwningFaction();
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
	TradeModal->Init(GetInventory(), Cast<UItemStackObject>(ItemListBox->GetCurrentOption())->Item, Targets);

	TradeModal->OnConfirmed.Clear();
	TradeModal->OnConfirmed.AddUObject<UInventoryUI>(this, &UInventoryUI::HandleTradeConfirmed);

	CurrentModal = TradeModal;
}

void UInventoryUI::HandleTradeConfirmed(const FItemStack Trade, AStructure* Target) const
{
	if(Trade.Quantity > 0)
	{
		GetInventory()->AddQuantity(Trade.Item, Trade.Quantity);
		Target->GetInventory()->RemoveQuantity(Trade.Item, Trade.Quantity);
	}
	else
	{
		GetInventory()->RemoveQuantity(Trade.Item, Trade.Quantity);
		Target->GetInventory()->AddQuantity(Trade.Item, Trade.Quantity);
	}
	GetInventory()->GetStructure()->GetOwningFaction()->ChangeBalance(-Trade.Quantity * Trade.Item->Value);
	Target->GetOwningFaction()->ChangeBalance(Trade.Quantity * Trade.Item->Value);
}

void UInventoryUI::HandleTransfer()
{
	const UUIBase* Base = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UUIBase>(this);

	if(IsValid(CurrentModal))
	{
		CurrentModal->DeactivateWidget();
		CurrentModal = nullptr;
	}

	TArray<AStructure*> Targets = Structure->GetLocation()->GetInTree();
	Targets.Remove(Structure);
	
	UInventoryTransferModal* TransferModal = Base->PushModal<UInventoryTransferModal>(TransferModalClass);
	TransferModal->Init(GetInventory(), Cast<UItemStackObject>(ItemListBox->GetCurrentOption())->Item, Targets);

	TransferModal->OnConfirmed.Clear();
	TransferModal->OnConfirmed.AddUObject<UInventoryUI>(this, &UInventoryUI::HandleTransferConfirmed);

	CurrentModal = TransferModal;
}

void UInventoryUI::HandleTransferConfirmed(const FItemStack Transfer, AStructure* Target) const
{
	GetInventory()->RemoveQuantity(Transfer.Item, Transfer.Quantity);
	Target->GetInventory()->AddQuantity(Transfer.Item, Transfer.Quantity);
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
	DisposeModal->Init(GetInventory(), Cast<UItemStackObject>(ItemListBox->GetCurrentOption())->Item);

	DisposeModal->OnConfirmed.Clear();
	DisposeModal->OnConfirmed.AddUObject<UInventoryUI>(this, &UInventoryUI::HandleDisposeConfirmed);

	CurrentModal = DisposeModal;
}

void UInventoryUI::HandleDisposeConfirmed(const FItemStack Dispose) const
{
	GetInventory()->RemoveQuantity(Dispose.Item, Dispose.Quantity);
}
