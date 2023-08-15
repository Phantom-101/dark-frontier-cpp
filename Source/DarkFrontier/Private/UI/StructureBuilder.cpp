// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/StructureBuilder.h"
#include "CommonButtonBase.h"
#include "Libraries/UIBlueprintLibrary.h"
#include "Structures/StructureController.h"
#include "UI/CompatibleSectionSelect.h"
#include "UI/StructureLayoutEditor.h"
#include "Structures/StructureSection.h"
#include "Structures/StructureSectionSlot.h"
#include "UI/ConfirmationModal.h"
#include "UI/UIBase.h"

void UStructureBuilder::NativeConstruct()
{
	Super::NativeConstruct();

	UIBase = Cast<AStructureController>(GetWorld()->GetFirstPlayerController())->UIBaseWidget;

	CloseButton->OnClicked().Clear();
	CloseButton->OnClicked().AddUObject<UStructureBuilder>(this, &UStructureBuilder::OnCloseButtonClicked);

	SetSelectedSectionSlot(nullptr);
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

void UStructureBuilder::SetParams(AStructure* NewTargetStructure, TArray<TSubclassOf<AStructureSection>> NewAvailableSectionTypes, TArray<TSubclassOf<AStructureEquipment>> NewAvailableEquipmentTypes)
{
	TargetStructure = NewTargetStructure;
	AvailableSectionTypes = NewAvailableSectionTypes;
	AvailableEquipmentTypes = NewAvailableEquipmentTypes;
	UpdateView();
}

void UStructureBuilder::UpdateView()
{
	LayoutEditor->UpdateView(TargetStructure);
}

TArray<TSubclassOf<AStructureSection>> UStructureBuilder::GetAvailableSectionTypes()
{
	return AvailableSectionTypes;
}

UStructureSectionSlot* UStructureBuilder::GetSelectedSectionSlot()
{
	return SelectedSectionSlot;
}

void UStructureBuilder::SetSelectedSectionSlot(UStructureSectionSlot* NewSlot)
{
	SelectedSectionSlot = NewSlot;
	if(SelectedSectionSlot)
	{
		SectionSelect->SetVisibility(ESlateVisibility::Visible);
		SectionSelect->UpdateView();
	}
	else
	{
		SectionSelect->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UStructureBuilder::AttachSectionType(TSubclassOf<AStructureSection> SectionType, FText SlotName)
{
	AStructureSection* Section = Cast<AStructureSection>(GetWorld()->SpawnActor(SectionType));
	Section->GetSectionSlotByName(SlotName)->Attach(SelectedSectionSlot);
	SetSelectedSectionSlot(nullptr);
	UpdateView();
}

void UStructureBuilder::RemoveAttachedSection(UStructureSectionSlot* Target)
{
	Target->AttachedSlot->OwningSection->RemoveSection();
	UpdateView();
}

void UStructureBuilder::DisconnectAttachedSection(UStructureSectionSlot* Target)
{
	Target->Detach();
	UpdateView();
}

TArray<TSubclassOf<AStructureEquipment>> UStructureBuilder::GetAvailableEquipmentTypes()
{
	return AvailableEquipmentTypes;
}

UStructureEquipmentSlot* UStructureBuilder::GetSelectedEquipmentSlot()
{
	return SelectedEquipmentSlot;
}


void UStructureBuilder::SetSelectedEquipmentSlot(UStructureEquipmentSlot* NewSlot)
{
	SelectedEquipmentSlot = NewSlot;
	// todo update equipment select view
}

void UStructureBuilder::AttachEquipmentType(TSubclassOf<AStructureEquipment> EquipmentType, FText SlotName)
{
	
}

void UStructureBuilder::RemoveAttachedEquipment(UStructureEquipmentSlot* Target)
{
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
