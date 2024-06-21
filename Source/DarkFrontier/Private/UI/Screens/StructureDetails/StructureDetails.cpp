// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructureDetails.h"
#include "CommonButtonBase.h"
#include "Log.h"
#include "Components/WidgetSwitcher.h"
#include "Structures/Structure.h"
#include "Structures/StructureController.h"
#include "Structures/StructureLayout.h"
#include "Structures/StructurePart.h"
#include "Structures/StructureSlot.h"
#include "UI/Screens/StructureDetails/StructureInfo.h"
#include "UI/Screens/StructureDetails/StructurePartInfo.h"
#include "UI/Screens/StructureDetails/StructurePartSelector.h"
#include "UI/Screens/StructureDetails/StructureSlotInfo.h"
#include "UI/Screens/StructureDetails/StructureSlotSelector.h"

void UStructureDetails::NativeConstruct()
{
	Super::NativeConstruct();

	BackgroundButton->OnClicked().Clear();
	BackgroundButton->OnClicked().AddUObject<UStructureDetails>(this, &UStructureDetails::OnBackgroundClicked);
	ApplyButton->OnClicked().Clear();
	ApplyButton->OnClicked().AddUObject<UStructureDetails>(this, &UStructureDetails::OnApplyButtonClicked);
	ExitButton->OnClicked().Clear();
	ExitButton->OnClicked().AddUObject<UStructureDetails>(this, &UStructureDetails::OnExitButtonClicked);

	AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	if(IsValid(Controller))
	{
		if(!OnLayoutChangedHandle.IsValid())
		{
			OnLayoutChangedHandle = Controller->OnLayoutChanged.AddUObject<UStructureDetails>(this, &UStructureDetails::OnLayoutChanged);
		}
	}
}

void UStructureDetails::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(IsValid(TargetStructure))
	{
		ApplyButton->SetIsEnabled(TargetStructure->IsLayoutValid());
	}
	else
	{
		ApplyButton->SetIsEnabled(false);
	}
}

TOptional<FUIInputConfig> UStructureDetails::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::CaptureDuringRightMouseDown);
}

void UStructureDetails::ClearAvailableParts()
{
	AvailableParts.Empty();
}

void UStructureDetails::SetAvailableParts(const TArray<TSubclassOf<AStructurePart>>& InTypes)
{
	AvailableParts = InTypes;
}

void UStructureDetails::InitStructure(AStructure* InStructure)
{
	TargetStructure = InStructure;
	SavedLayout = FStructureLayout(InStructure);

	UE_LOG(LogDarkFrontier, Log, TEXT("Initialized structure details view for %s"), *InStructure->GetFullName());
}

void UStructureDetails::SelectStructure()
{
	InfoSwitcher->SetActiveWidget(StructureInfo);
	StructureInfo->SetTarget(TargetStructure);
	BaseSlot = nullptr;
	PartType = nullptr;
	SelectorSwitcher->SetActiveWidget(NoSelector);
}

void UStructureDetails::SelectPart(AStructurePart* InPart)
{
	InfoSwitcher->SetActiveWidget(PartInfo);
	PartInfo->SetTarget(InPart);
	BaseSlot = nullptr;
	PartType = nullptr;
	SelectorSwitcher->SetActiveWidget(NoSelector);
}

void UStructureDetails::SelectSlot(UStructureSlot* InSlot)
{
	InfoSwitcher->SetActiveWidget(SlotInfo);
	SlotInfo->SetTarget(InSlot);
	BaseSlot = nullptr;
	PartType = nullptr;
	SelectorSwitcher->SetActiveWidget(NoSelector);
}

void UStructureDetails::SetBaseSlot(UStructureSlot* InSlot)
{
	BaseSlot = InSlot;
	PartType = nullptr;
	PartSelector->PopulateOptions(AvailableParts, BaseSlot);
	SelectorSwitcher->SetActiveWidget(PartSelector);
}

void UStructureDetails::SetPartType(const TSubclassOf<AStructurePart> InClass)
{
	PartType = InClass;
	SlotSelector->PopulateOptions(PartType, BaseSlot);
	SelectorSwitcher->SetActiveWidget(SlotSelector);
}

void UStructureDetails::AttachWithSlotName(const FText& InName)
{
	AStructurePart* Section = Cast<AStructurePart>(GetWorld()->SpawnActor(PartType));
	Section->GetSlot(InName)->TryAttach(BaseSlot);
	
	BaseSlot = nullptr;
	PartType = nullptr;
	SelectorSwitcher->SetActiveWidget(NoSelector);
}

void UStructureDetails::OnBackgroundClicked() const
{
	SelectorSwitcher->SetActiveWidget(NoSelector);
}

void UStructureDetails::OnLayoutChanged()
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

void UStructureDetails::OnApplyButtonClicked()
{
	if(!TargetStructure->IsLayoutValid()) return;

	DeactivateWidget();
}

void UStructureDetails::OnExitButtonClicked()
{
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
	
	DeactivateWidget();
}
