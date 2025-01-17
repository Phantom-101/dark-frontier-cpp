// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/InventoryUI/InventoryUI.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "Items/Inventory.h"
#include "Items/Item.h"
#include "Items/ItemStack.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"
#include "Structures/Structure.h"
#include "Structures/StructureLocation.h"
#include "UI/Screens/UIBase.h"
#include "UI/Screens/InventoryUI/InventoryDisposeModal.h"
#include "UI/Screens/InventoryUI/InventoryOption.h"
#include "UI/Screens/InventoryUI/ItemList.h"
#include "UI/Widgets/Modals/ListBoxModal.h"
#include "UI/Widgets/Visuals/InfoField.h"

void UInventoryUI::NativeConstruct()
{
	Super::NativeConstruct();

	SwitchButton->OnClicked().Clear();
	SwitchButton->OnClicked().AddUObject<UInventoryUI>(this, &UInventoryUI::HandleSwitch);
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
	AStructure* Root = CurrentStructure;
	while(Root->GetLocation()->GetDockStructure() != nullptr)
	{
		Root = Root->GetLocation()->GetDockStructure();
	}
	
	TArray<UObject*> Structures;
	Structures.Add(Root);

	int Index = 0;
	while(Index < Structures.Num())
	{
		Structures.Append(Cast<AStructure>(Structures[Index])->GetLocation()->GetDockers());
		Index++;
	}

	const UUIBase* Base = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UUIBase>(this);

	if(SwitchModal != nullptr)
	{
		HandleSwitchCanceled();
	}
	
	SwitchModal = Base->PushModal<UListBoxModal>(ListBoxModalClass);
	SwitchModal->SetOptionsWithInitial(Structures, CurrentStructure);
	SwitchModal->SetBuilder([Owner = SwitchModal, Class = InventoryOptionClass](UObject* Structure)
	{
		UInventoryOption* Option = CreateWidget<UInventoryOption>(Owner, Class);
		Option->Init(Cast<AStructure>(Structure));
		return Option;
	});

	SwitchModal->OnConfirmed.Clear();
	SwitchModal->OnConfirmed.AddUObject<UInventoryUI>(this, &UInventoryUI::HandleSwitchConfirmed);
	SwitchModal->OnCanceled.Clear();
	SwitchModal->OnCanceled.AddUObject<UInventoryUI>(this, &UInventoryUI::HandleSwitchCanceled);
}

void UInventoryUI::HandleSwitchConfirmed(UObject* Selection)
{
	SetCurrentStructure(Cast<AStructure>(Selection));
	
	HandleSwitchCanceled();
}

void UInventoryUI::HandleSwitchCanceled()
{
	SwitchModal->DeactivateWidget();
	SwitchModal = nullptr;
}

void UInventoryUI::HandleDispose()
{
	const UUIBase* Base = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UUIBase>(this);

	if(DisposeModal != nullptr)
	{
		HandleDisposeCanceled();
	}
	
	DisposeModal = Base->PushModal<UInventoryDisposeModal>(DisposeModalClass);
	DisposeModal->Init(ItemList->GetInventory(), ItemList->GetSelectedItem());

	DisposeModal->OnConfirmed.Clear();
	DisposeModal->OnConfirmed.AddUObject<UInventoryUI>(this, &UInventoryUI::HandleDisposeConfirmed);
	DisposeModal->OnCanceled.Clear();
	DisposeModal->OnCanceled.AddUObject<UInventoryUI>(this, &UInventoryUI::HandleDisposeCanceled);
}

void UInventoryUI::HandleDisposeConfirmed(const FItemStack Dispose)
{
	ItemList->GetInventory()->RemoveItems(Dispose.Item, Dispose.Quantity);
	
	HandleDisposeCanceled();
}

void UInventoryUI::HandleDisposeCanceled()
{
	DisposeModal->DeactivateWidget();
	DisposeModal = nullptr;
}
