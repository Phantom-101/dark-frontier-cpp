// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/BuildUI/BuildUI.h"
#include "CommonButtonBase.h"
#include "Log.h"
#include "Components/WidgetSwitcher.h"
#include "Structures/Structure.h"
#include "Structures/StructureController.h"
#include "Structures/StructureLayoutData.h"
#include "Structures/StructurePart.h"
#include "Structures/StructureSlot.h"
#include "UI/Screens/BuildUI/StructureInfo.h"
#include "UI/Screens/BuildUI/StructurePartInfo.h"
#include "UI/Screens/BuildUI/StructurePartSelector.h"
#include "UI/Screens/BuildUI/StructureSlotInfo.h"
#include "UI/Screens/BuildUI/StructureSlotSelector.h"

void UBuildUI::NativeConstruct()
{
	Super::NativeConstruct();

	BackgroundButton->OnClicked().Clear();
	BackgroundButton->OnClicked().AddUObject<UBuildUI>(this, &UBuildUI::OnBackgroundClicked);
	ExitButton->OnClicked().Clear();
	ExitButton->OnClicked().AddUObject<UBuildUI>(this, &UBuildUI::OnExitButtonClicked);

	AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	if(IsValid(Controller))
	{
		if(!OnLayoutChangedHandle.IsValid())
		{
			OnLayoutChangedHandle = Controller->OnLayoutChanged.AddUObject<UBuildUI>(this, &UBuildUI::OnLayoutChanged);
		}
	}
}

void UBuildUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

TOptional<FUIInputConfig> UBuildUI::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::CaptureDuringRightMouseDown);
}

void UBuildUI::ClearAvailableParts()
{
	AvailableParts.Empty();
}

void UBuildUI::SetAvailableParts(const TArray<TSubclassOf<AStructurePart>>& InTypes)
{
	AvailableParts = InTypes;
}

void UBuildUI::InitStructure(AStructure* InStructure)
{
	TargetStructure = InStructure;
	SavedLayout = FStructureLayoutData(InStructure);

	UE_LOG(LogDarkFrontier, Log, TEXT("Initialized structure details view for %s"), *InStructure->GetFullName());
}

void UBuildUI::SelectStructure()
{
	InfoSwitcher->SetActiveWidget(StructureInfo);
	StructureInfo->SetTarget(TargetStructure);
	BaseSlot = nullptr;
	PartType = nullptr;
	SelectorSwitcher->SetActiveWidget(NoSelector);
}

void UBuildUI::SelectPart(AStructurePart* InPart)
{
	InfoSwitcher->SetActiveWidget(PartInfo);
	PartInfo->SetTarget(InPart);
	BaseSlot = nullptr;
	PartType = nullptr;
	SelectorSwitcher->SetActiveWidget(NoSelector);
}

void UBuildUI::SelectSlot(UStructureSlot* InSlot)
{
	InfoSwitcher->SetActiveWidget(SlotInfo);
	SlotInfo->SetTarget(InSlot);
	BaseSlot = nullptr;
	PartType = nullptr;
	SelectorSwitcher->SetActiveWidget(NoSelector);
}

void UBuildUI::SetBaseSlot(UStructureSlot* InSlot)
{
	BaseSlot = InSlot;
	PartType = nullptr;
	PartSelector->PopulateOptions(AvailableParts, BaseSlot);
	SelectorSwitcher->SetActiveWidget(PartSelector);
}

void UBuildUI::SetPartType(const TSubclassOf<AStructurePart>& InClass)
{
	PartType = InClass;
	SelectorSwitcher->SetActiveWidget(SlotSelector);

	// Call this after active widget change as populate options will automatically call attach with slot name
	// In the event that only one slot is compatible, in which case the active widget will be set to no selector
	SlotSelector->PopulateOptions(PartType, BaseSlot);
}

void UBuildUI::AttachWithSlotName(const FText& InName)
{
	AStructurePart* Section = Cast<AStructurePart>(GetWorld()->SpawnActor(PartType));
	Section->GetSlot(InName)->TryAttach(BaseSlot);

	if(!TargetStructure->GetLayout()->IsValid())
	{
		UE_LOG(LogDarkFrontier, Log, TEXT("Layout validation error"))
		Section->DetachSlots();
	}
	
	BaseSlot = nullptr;
	PartType = nullptr;
	SelectorSwitcher->SetActiveWidget(NoSelector);
}

void UBuildUI::OnBackgroundClicked() const
{
	SelectorSwitcher->SetActiveWidget(NoSelector);
}

void UBuildUI::OnLayoutChanged()
{
	if((InfoSwitcher->GetActiveWidget() == PartInfo && !IsValid(PartInfo->GetTarget())) ||
		(InfoSwitcher->GetActiveWidget() == SlotInfo && !IsValid(SlotInfo->GetTarget())))
	{
		InfoSwitcher->SetActiveWidget(StructureInfo);
		BaseSlot = nullptr;
		PartType = nullptr;
		SelectorSwitcher->SetActiveWidget(NoSelector);
	}
}

void UBuildUI::OnExitButtonClicked()
{
	DeactivateWidget();

	/*
	if(StructureClass == nullptr)
	{
		UE_LOG(LogDarkFrontier, Error, TEXT("Structure class is null"));
		return;
	}
	
	FActorSpawnParameters Parameters;
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AStructure* NewStructure = GetWorld()->SpawnActor<AStructure>(StructureClass, Parameters);
	
	if(NewStructure == nullptr)
	{
		UE_LOG(LogDarkFrontier, Error, TEXT("Structure details new structure is null"));
		return;
	}

	AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	if(IsValid(Controller) && Controller->GetPawn() == TargetStructure)
	{
		Controller->Possess(NewStructure);
	}

	// Load layout after switching pawns to make sure layout change subscribers fetch the correct pawn
	NewStructure->LoadLayout(SavedLayout);
	
	TargetStructure->TryDestroy();
	
	 */
}
