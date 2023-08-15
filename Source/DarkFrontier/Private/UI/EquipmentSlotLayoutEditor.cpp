// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/EquipmentSlotLayoutEditor.h"
#include "CommonBorder.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/ListViewBase.h"
#include "UI/StructureBuilder.h"
#include "Structures/StructureEquipment.h"
#include "Structures/StructureEquipmentSlot.h"
#include "Libraries/UIBlueprintLibrary.h"

void UEquipmentSlotLayoutEditor::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	EquipmentSlot = Cast<UStructureEquipmentSlot>(ListItemObject);
	StructureBuilder = UUIBlueprintLibrary::GetParentWidgetOfClass<UStructureBuilder>(GetOwningListView());

	NameText->SetText(EquipmentSlot->SlotName);
	if(EquipmentSlot->AttachedEquipment)
	{
		TypeText->SetText(EquipmentSlot->AttachedEquipment->GetClass()->GetDisplayNameText());

		AddButton->SetIsInteractionEnabled(false);
		RemoveButton->SetIsInteractionEnabled(true);
		ViewButton->SetIsInteractionEnabled(true);
	}
	else
	{
		TypeText->SetText(FText::FromString("None"));

		AddButton->SetIsInteractionEnabled(true);
		RemoveButton->SetIsInteractionEnabled(false);
		ViewButton->SetIsInteractionEnabled(false);
	}
	
	AddButton->OnClicked().AddUObject<UEquipmentSlotLayoutEditor>(this, &UEquipmentSlotLayoutEditor::OnAddButtonClicked);
	RemoveButton->OnClicked().AddUObject<UEquipmentSlotLayoutEditor>(this, &UEquipmentSlotLayoutEditor::OnRemoveButtonClicked);
	ViewButton->OnClicked().AddUObject<UEquipmentSlotLayoutEditor>(this, &UEquipmentSlotLayoutEditor::OnViewButtonClicked);
}

void UEquipmentSlotLayoutEditor::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	Highlight->SetBrushColor(StructureBuilder->GetSelectedEquipmentSlot() == EquipmentSlot ? HighlightColor : FLinearColor::Transparent);
}

void UEquipmentSlotLayoutEditor::OnAddButtonClicked() const
{
	StructureBuilder->SetSelectedEquipmentSlot(EquipmentSlot);
}

void UEquipmentSlotLayoutEditor::OnRemoveButtonClicked() const
{
}

void UEquipmentSlotLayoutEditor::OnViewButtonClicked() const
{
	GetWorld()->GetFirstPlayerController()->SetViewTarget(EquipmentSlot->AttachedEquipment);
}
