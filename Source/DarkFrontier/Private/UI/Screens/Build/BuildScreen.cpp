// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Build/BuildScreen.h"
#include "CommonButtonBase.h"
#include "Log.h"
#include "Components/WidgetSwitcher.h"
#include "Structures/Structure.h"
#include "Structures/StructureController.h"
#include "Structures/StructureLayoutData.h"
#include "Structures/StructurePart.h"
#include "Structures/StructureSlot.h"
#include "UI/Screens/Build/StructureInfo.h"
#include "UI/Screens/Build/StructurePartInfo.h"
#include "UI/Screens/Build/StructurePartSelector.h"
#include "UI/Screens/Build/StructureSlotInfo.h"
#include "UI/Screens/Build/StructureSlotSelector.h"

void UBuildScreen::NativeConstruct()
{
	Super::NativeConstruct();

	BackgroundButton->OnClicked().Clear();
	BackgroundButton->OnClicked().AddUObject<UBuildScreen>(this, &UBuildScreen::OnBackgroundClicked);
	ExitButton->OnClicked().Clear();
	ExitButton->OnClicked().AddUObject<UBuildScreen>(this, &UBuildScreen::OnExitButtonClicked);

	AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	if(IsValid(Controller))
	{
		if(!OnLayoutChangedHandle.IsValid())
		{
			OnLayoutChangedHandle = Controller->OnLayoutChanged.AddUObject<UBuildScreen>(this, &UBuildScreen::OnLayoutChanged);
		}
	}
}

void UBuildScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

TOptional<FUIInputConfig> UBuildScreen::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::CaptureDuringRightMouseDown);
}

void UBuildScreen::ClearAvailableParts()
{
	AvailableParts.Empty();
}

void UBuildScreen::SetAvailableParts(const TArray<TSubclassOf<AStructurePart>>& InTypes)
{
	AvailableParts = InTypes;
}

void UBuildScreen::InitStructure(AStructure* InStructure)
{
	TargetStructure = InStructure;
	SavedLayout = FStructureLayoutData(InStructure);

	UE_LOG(LogDarkFrontier, Log, TEXT("Initialized structure details view for %s"), *InStructure->GetFullName());
}

void UBuildScreen::SelectStructure()
{
	InfoSwitcher->SetActiveWidget(StructureInfo);
	StructureInfo->SetTarget(TargetStructure);
	BaseSlot = nullptr;
	PartType = nullptr;
	SelectorSwitcher->SetActiveWidget(NoSelector);
}

void UBuildScreen::SelectPart(AStructurePart* InPart)
{
	InfoSwitcher->SetActiveWidget(PartInfo);
	PartInfo->SetTarget(InPart);
	BaseSlot = nullptr;
	PartType = nullptr;
	SelectorSwitcher->SetActiveWidget(NoSelector);
}

void UBuildScreen::SelectSlot(UStructureSlot* InSlot)
{
	InfoSwitcher->SetActiveWidget(SlotInfo);
	SlotInfo->SetTarget(InSlot);
	BaseSlot = nullptr;
	PartType = nullptr;
	SelectorSwitcher->SetActiveWidget(NoSelector);
}

void UBuildScreen::SetBaseSlot(UStructureSlot* InSlot)
{
	BaseSlot = InSlot;
	PartType = nullptr;
	PartSelector->PopulateOptions(AvailableParts, BaseSlot);
	SelectorSwitcher->SetActiveWidget(PartSelector);
}

void UBuildScreen::SetPartType(const TSubclassOf<AStructurePart>& InClass)
{
	PartType = InClass;
	SelectorSwitcher->SetActiveWidget(SlotSelector);

	// Call this after active widget change as populate options will automatically call attach with slot name
	// In the event that only one slot is compatible, in which case the active widget will be set to no selector
	SlotSelector->PopulateOptions(PartType, BaseSlot);
}

void UBuildScreen::AttachWithSlotName(const FText& InName)
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

void UBuildScreen::OnBackgroundClicked() const
{
	SelectorSwitcher->SetActiveWidget(NoSelector);
}

void UBuildScreen::OnLayoutChanged()
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

void UBuildScreen::OnExitButtonClicked()
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
