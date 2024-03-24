// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/StructureBuilder.h"
#include "CommonButtonBase.h"
#include "Libraries/UIBlueprintLibrary.h"
#include "Structures/Structure.h"
#include "Structures/StructureController.h"
#include "UI/CompatibleStructurePartSelect.h"
#include "UI/StructureLayoutEditor.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartSlot.h"
#include "UI/ConfirmationModal.h"
#include "UI/Screens/UIBase.h"

void UStructureBuilder::NativeConstruct()
{
	Super::NativeConstruct();

	UIBase = Cast<AStructureController>(GetWorld()->GetFirstPlayerController())->UIBaseWidget;

	CloseButton->OnClicked().Clear();
	CloseButton->OnClicked().AddUObject<UStructureBuilder>(this, &UStructureBuilder::OnCloseButtonClicked);

	SetSelectedPartSlot(nullptr);
}

void UStructureBuilder::NativeOnActivated()
{
	Super::NativeOnActivated();
	
	GetDesiredFocusTarget()->SetFocus();
}

UWidget* UStructureBuilder::NativeGetDesiredFocusTarget() const
{
	return CloseButton;
}

TOptional<FUIInputConfig> UStructureBuilder::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
}

void UStructureBuilder::SetParams(AStructure* NewTargetStructure, const TArray<TSubclassOf<AStructurePart>> InAvailableParts)
{
	TargetStructure = NewTargetStructure;
	AvailableParts = InAvailableParts;
	UpdateView();
}

void UStructureBuilder::UpdateView() const
{
	LayoutEditor->UpdateView(TargetStructure);
}

TArray<TSubclassOf<AStructurePart>> UStructureBuilder::GetAvailableParts()
{
	return AvailableParts;
}

UStructurePartSlot* UStructureBuilder::GetSelectedPartSlot() const
{
	return SelectedPartSlot;
}

void UStructureBuilder::SetSelectedPartSlot(UStructurePartSlot* NewSlot)
{
	SelectedPartSlot = NewSlot;
	if(SelectedPartSlot)
	{
		PartSelect->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		PartSelect->UpdateView();
	}
	else
	{
		PartSelect->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UStructureBuilder::AttachPartOfType(const TSubclassOf<AStructurePart> PartClass, const FText SlotName)
{
	AStructurePart* Section = Cast<AStructurePart>(GetWorld()->SpawnActor(PartClass));
	Section->GetSlot(SlotName)->Attach(SelectedPartSlot);
	// Assume part layout invalidity is due to added section
	if(!Section->OwningStructure->IsPartLayoutValid())
	{
		Section->RemovePart();
	}
	SetSelectedPartSlot(nullptr);
	UpdateView();
}

void UStructureBuilder::RemoveAttachedPart(UStructurePartSlot* Target) const
{
	Target->AttachedSlot->OwningPart->RemovePart();
	UpdateView();
}

void UStructureBuilder::DisconnectAttachedPart(UStructurePartSlot* Target) const
{
	Target->Detach();
	UpdateView();
}

void UStructureBuilder::OnCloseButtonClicked()
{
	UConfirmationModal* Modal = UIBase->PushModal<UConfirmationModal>(ConfirmationModalClass);
	Modal->SetText(FText::AsCultureInvariant("Close"), FText::AsCultureInvariant("Are you sure you want to close the structure builder tool?"));
	Modal->OnConfirmed.AddUObject<UStructureBuilder>(this, &UStructureBuilder::OnCloseModalConfirmed);
}

void UStructureBuilder::OnCloseModalConfirmed()
{
	DeactivateWidget();
}
