// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/StructurePartSlotLayoutEditor.h"
#include "CommonBorder.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ListViewBase.h"
#include "UI/StructureBuilder.h"
#include "Structures/Structure.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartSlot.h"
#include "Libraries/UIBlueprintLibrary.h"

void UStructurePartSlotLayoutEditor::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	PartSlot = Cast<UStructurePartSlot>(ListItemObject);
	StructureBuilder = UUIBlueprintLibrary::GetParentWidgetOfClass<UStructureBuilder>(GetOwningListView());

	NameText->SetText(PartSlot->GetSlotName());
	if(PartSlot->GetAttachedSlot())
	{
		TypeText->SetText(PartSlot->GetAttachedSlot()->GetOwningPart()->GetTypeName());
		IdText->SetText(FText::FromString(FString::Printf(TEXT("#%i"), PartSlot->GetAttachedSlot()->GetOwningPart()->GetPartId())));

		AddButton->SetIsInteractionEnabled(false);
		RemoveButton->SetIsInteractionEnabled(PartSlot->GetAttachedSlot()->GetOwningPart() != PartSlot->GetOwningPart()->GetOwningStructure()->GetRootPart());
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

	AddButton->OnClicked().Clear();
	AddButton->OnClicked().AddUObject<UStructurePartSlotLayoutEditor>(this, &UStructurePartSlotLayoutEditor::OnAddButtonClicked);
	RemoveButton->OnClicked().Clear();
	RemoveButton->OnClicked().AddUObject<UStructurePartSlotLayoutEditor>(this, &UStructurePartSlotLayoutEditor::OnRemoveButtonClicked);
	DisconnectButton->OnClicked().Clear();
	DisconnectButton->OnClicked().AddUObject<UStructurePartSlotLayoutEditor>(this, &UStructurePartSlotLayoutEditor::OnDisconnectButtonClicked);
	ViewButton->OnClicked().Clear();
	ViewButton->OnClicked().AddUObject<UStructurePartSlotLayoutEditor>(this, &UStructurePartSlotLayoutEditor::OnViewButtonClicked);
}

void UStructurePartSlotLayoutEditor::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	Highlight->SetBrushColor(StructureBuilder->GetSelectedPartSlot() == PartSlot ? HighlightColor : FLinearColor::Transparent);
}

void UStructurePartSlotLayoutEditor::OnAddButtonClicked() const
{
	StructureBuilder->SetSelectedPartSlot(PartSlot);
}

void UStructurePartSlotLayoutEditor::OnRemoveButtonClicked() const
{
	StructureBuilder->RemoveAttachedPart(PartSlot);
}

void UStructurePartSlotLayoutEditor::OnDisconnectButtonClicked() const
{
	StructureBuilder->DisconnectAttachedPart(PartSlot);
}

void UStructurePartSlotLayoutEditor::OnViewButtonClicked() const
{
	GetWorld()->GetFirstPlayerController()->SetViewTarget(PartSlot->GetAttachedSlot()->GetOwningPart());
}
