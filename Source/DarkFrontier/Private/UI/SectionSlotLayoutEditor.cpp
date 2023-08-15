// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/SectionSlotLayoutEditor.h"
#include "CommonBorder.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ListViewBase.h"
#include "UI/StructureBuilder.h"
#include "Structures/Structure.h"
#include "Structures/StructureSection.h"
#include "Structures/StructureSectionSlot.h"
#include "Libraries/UIBlueprintLibrary.h"

void USectionSlotLayoutEditor::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	SectionSlot = Cast<UStructureSectionSlot>(ListItemObject);
	StructureBuilder = UUIBlueprintLibrary::GetParentWidgetOfClass<UStructureBuilder>(GetOwningListView());

	NameText->SetText(SectionSlot->SlotName);
	if(SectionSlot->AttachedSlot)
	{
		TypeText->SetText(SectionSlot->AttachedSlot->OwningSection->GetClass()->GetDisplayNameText());
		IdText->SetText(FText::FromString(FString::Printf(TEXT("#%i"), SectionSlot->AttachedSlot->OwningSection->SectionId)));

		AddButton->SetIsInteractionEnabled(false);
		RemoveButton->SetIsInteractionEnabled(SectionSlot->AttachedSlot->OwningSection != SectionSlot->OwningSection->OwningStructure->GetRootSection());
		DisconnectButton->SetIsInteractionEnabled(true);
		ViewButton->SetIsInteractionEnabled(true);
	}
	else
	{
		TypeText->SetText(FText::FromString("None"));
		IdText->SetText(FText::GetEmpty());

		AddButton->SetIsInteractionEnabled(true);
		RemoveButton->SetIsInteractionEnabled(false);
		DisconnectButton->SetIsInteractionEnabled(false);
		ViewButton->SetIsInteractionEnabled(false);
	}

	AddButton->OnClicked().AddUObject<USectionSlotLayoutEditor>(this, &USectionSlotLayoutEditor::OnAddButtonClicked);
	RemoveButton->OnClicked().AddUObject<USectionSlotLayoutEditor>(this, &USectionSlotLayoutEditor::OnRemoveButtonClicked);
	DisconnectButton->OnClicked().AddUObject<USectionSlotLayoutEditor>(this, &USectionSlotLayoutEditor::OnDisconnectButtonClicked);
	ViewButton->OnClicked().AddUObject<USectionSlotLayoutEditor>(this, &USectionSlotLayoutEditor::OnViewButtonClicked);
}

void USectionSlotLayoutEditor::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	Highlight->SetBrushColor(StructureBuilder->GetSelectedSectionSlot() == SectionSlot ? HighlightColor : FLinearColor::Transparent);
}

void USectionSlotLayoutEditor::OnAddButtonClicked() const
{
	StructureBuilder->SetSelectedSectionSlot(SectionSlot);
}

void USectionSlotLayoutEditor::OnRemoveButtonClicked() const
{
	StructureBuilder->RemoveAttachedSection(SectionSlot);
}

void USectionSlotLayoutEditor::OnDisconnectButtonClicked() const
{
	StructureBuilder->DisconnectAttachedSection(SectionSlot);
}

void USectionSlotLayoutEditor::OnViewButtonClicked() const
{
	GetWorld()->GetFirstPlayerController()->SetViewTarget(SectionSlot->AttachedSlot->OwningSection);
}
