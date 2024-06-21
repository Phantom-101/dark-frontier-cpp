// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/StructureSlotLayoutEditor.h"
#include "CommonBorder.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ListViewBase.h"
#include "UI/StructureBuilder.h"
#include "Structures/Structure.h"
#include "Structures/StructurePart.h"
#include "Structures/StructureSlot.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"

void UStructureSlotLayoutEditor::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	TargetSlot = Cast<UStructureSlot>(ListItemObject);
	StructureBuilder = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UStructureBuilder>(GetOwningListView());

	NameText->SetText(TargetSlot->GetSlotName());
	if(TargetSlot->GetAttachedSlot())
	{
		TypeText->SetText(TargetSlot->GetAttachedSlot()->GetOwningPart()->GetTypeName());
		IdText->SetText(FText::FromString(FString::Printf(TEXT("%s"), *TargetSlot->GetAttachedSlot()->GetOwningPart()->GetPartId())));

		AddButton->SetIsInteractionEnabled(false);
		RemoveButton->SetIsInteractionEnabled(TargetSlot->GetAttachedSlot()->GetOwningPart() != TargetSlot->GetOwningPart()->GetOwningStructure()->GetRootPart());
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
	AddButton->OnClicked().AddUObject<UStructureSlotLayoutEditor>(this, &UStructureSlotLayoutEditor::OnAddButtonClicked);
	RemoveButton->OnClicked().Clear();
	RemoveButton->OnClicked().AddUObject<UStructureSlotLayoutEditor>(this, &UStructureSlotLayoutEditor::OnRemoveButtonClicked);
	DisconnectButton->OnClicked().Clear();
	DisconnectButton->OnClicked().AddUObject<UStructureSlotLayoutEditor>(this, &UStructureSlotLayoutEditor::OnDisconnectButtonClicked);
	ViewButton->OnClicked().Clear();
	ViewButton->OnClicked().AddUObject<UStructureSlotLayoutEditor>(this, &UStructureSlotLayoutEditor::OnViewButtonClicked);
}

void UStructureSlotLayoutEditor::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	Highlight->SetBrushColor(StructureBuilder->GetSelectedSlot() == TargetSlot ? HighlightColor : FLinearColor::Transparent);
}

void UStructureSlotLayoutEditor::OnAddButtonClicked() const
{
	StructureBuilder->SetSelectedSlot(TargetSlot);
}

void UStructureSlotLayoutEditor::OnRemoveButtonClicked() const
{
	StructureBuilder->RemovePart(TargetSlot);
}

void UStructureSlotLayoutEditor::OnDisconnectButtonClicked() const
{
	StructureBuilder->DisconnectPart(TargetSlot);
}

void UStructureSlotLayoutEditor::OnViewButtonClicked() const
{
	GetWorld()->GetFirstPlayerController()->SetViewTarget(TargetSlot->GetAttachedSlot()->GetOwningPart());
}
