// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/StructureBuilder.h"
#include "CommonButtonBase.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"
#include "Structures/Structure.h"
#include "Structures/StructureController.h"
#include "UI/CompatibleStructurePartSelect.h"
#include "UI/StructureLayoutEditor.h"
#include "Structures/StructurePart.h"
#include "Structures/StructureSlot.h"
#include "UI/ConfirmationModal.h"
#include "UI/Screens/UIBase.h"

void UStructureBuilder::NativeConstruct()
{
	Super::NativeConstruct();

	UIBase = Cast<AStructureController>(GetWorld()->GetFirstPlayerController())->GetUIBaseWidget();

	CloseButton->OnClicked().Clear();
	CloseButton->OnClicked().AddUObject<UStructureBuilder>(this, &UStructureBuilder::OnCloseButtonClicked);

	SetSelectedSlot(nullptr);
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

UStructureSlot* UStructureBuilder::GetSelectedSlot() const
{
	return SelectedSlot;
}

void UStructureBuilder::SetSelectedSlot(UStructureSlot* NewSlot)
{
	SelectedSlot = NewSlot;
	if(SelectedSlot)
	{
		PartSelect->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		PartSelect->UpdateView();
	}
	else
	{
		PartSelect->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UStructureBuilder::AttachPart(const TSubclassOf<AStructurePart> PartType, const FText SlotName)
{
	AStructurePart* Section = Cast<AStructurePart>(GetWorld()->SpawnActor(PartType));
	Section->GetSlot(SlotName)->TryAttach(SelectedSlot);
	// Assume part layout invalidity is due to added section
	if(!Section->GetOwningStructure()->IsLayoutValid())
	{
		Section->DetachSlots();
	}
	SetSelectedSlot(nullptr);
	UpdateView();
}

void UStructureBuilder::RemovePart(UStructureSlot* Target) const
{
	Target->GetAttachedSlot()->GetOwningPart()->DetachSlots();
	UpdateView();
}

void UStructureBuilder::DisconnectPart(UStructureSlot* Target) const
{
	Target->TryDetach();
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
