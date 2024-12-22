// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/InventoryUI/InventoryUI.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "Items/Inventory.h"
#include "Items/Item.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"
#include "Structures/Structure.h"
#include "Structures/StructureLocation.h"
#include "UI/Screens/UIBase.h"
#include "UI/Screens/InventoryUI/InventoryOption.h"
#include "UI/Screens/InventoryUI/ItemList.h"
#include "UI/Widgets/InfoField.h"
#include "UI/Widgets/ListSelectionModal.h"

void UInventoryUI::NativeConstruct()
{
	Super::NativeConstruct();

	SwitchButton->OnClicked().Clear();
	SwitchButton->OnClicked().AddUObject<UInventoryUI>(this, &UInventoryUI::HandleSwitch);
}

void UInventoryUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
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

	if(CurrentModal != nullptr)
	{
		HandleSwitchCanceled();
	}
	
	CurrentModal = Base->PushModal<UListSelectionModal>(SelectionModalClass);
	CurrentModal->SetOptionsWithInitial(Structures, CurrentStructure);
	CurrentModal->SetBuilder([CurrentModal = this->CurrentModal, SelectionOptionClass = this->SelectionOptionClass](UObject* Structure)
	{
		UInventoryOption* Option = CreateWidget<UInventoryOption>(CurrentModal, SelectionOptionClass);
		Option->Init(Cast<AStructure>(Structure));
		return Option;
	});

	CurrentModal->OnConfirmed.Clear();
	CurrentModal->OnConfirmed.AddUObject<UInventoryUI>(this, &UInventoryUI::HandleSwitchConfirmed);
	CurrentModal->OnCanceled.Clear();
	CurrentModal->OnCanceled.AddUObject<UInventoryUI>(this, &UInventoryUI::HandleSwitchCanceled);
}

void UInventoryUI::HandleSwitchConfirmed(UObject* Selection)
{
	SetCurrentStructure(Cast<AStructure>(Selection));
	
	DisposeModal();
}

void UInventoryUI::HandleSwitchCanceled()
{
	DisposeModal();
}

void UInventoryUI::DisposeModal()
{
	CurrentModal->OnConfirmed.Clear();
	CurrentModal->OnCanceled.Clear();
	CurrentModal->DeactivateWidget();
	CurrentModal = nullptr;
}
