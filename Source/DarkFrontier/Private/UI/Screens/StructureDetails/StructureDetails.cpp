// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructureDetails.h"
#include "CommonButtonBase.h"
#include "Log.h"
#include "Components/WidgetSwitcher.h"
#include "Structures/Structure.h"
#include "Structures/StructureController.h"
#include "Structures/StructureLayout.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartSlot.h"
#include "UI/Screens/StructureDetails/StructureInfo.h"
#include "UI/Screens/StructureDetails/StructurePartInfo.h"
#include "UI/Screens/StructureDetails/StructurePartSelector.h"
#include "UI/Screens/StructureDetails/StructurePartSlotInfo.h"
#include "UI/Screens/StructureDetails/StructurePartSlotSelector.h"

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

void UStructureDetails::Init()
{
	AvailableParts.Empty();
}

void UStructureDetails::Init(const TArray<TSubclassOf<AStructurePart>>& InClasses)
{
	AvailableParts = InClasses;
}

void UStructureDetails::Select(AStructure* InStructure)
{
	TargetStructure = InStructure;

	SavedLayout = FStructureLayout(InStructure);
	
	InfoSwitcher->SetActiveWidget(StructureInfo);
	StructureInfo->SetTarget(TargetStructure);
	EditSlot = nullptr;
	EditClass = nullptr;
	SelectorSwitcher->SetActiveWidget(NoSelector);
}

void UStructureDetails::Select(AStructurePart* InPart)
{
	InfoSwitcher->SetActiveWidget(PartInfo);
	PartInfo->SetTarget(InPart);
	EditSlot = nullptr;
	EditClass = nullptr;
	SelectorSwitcher->SetActiveWidget(NoSelector);
}

void UStructureDetails::Select(UStructurePartSlot* InSlot)
{
	InfoSwitcher->SetActiveWidget(SlotInfo);
	SlotInfo->SetTarget(InSlot);
	EditSlot = nullptr;
	EditClass = nullptr;
	SelectorSwitcher->SetActiveWidget(NoSelector);
}

void UStructureDetails::Edit(UStructurePartSlot* InSlot)
{
	EditSlot = InSlot;
	EditClass = nullptr;
	PartSelector->PopulateOptions(AvailableParts, EditSlot);
	SelectorSwitcher->SetActiveWidget(PartSelector);
}

void UStructureDetails::Edit(const TSubclassOf<AStructurePart> InClass)
{
	EditClass = InClass;
	SlotSelector->PopulateOptions(EditClass, EditSlot);
	SelectorSwitcher->SetActiveWidget(SlotSelector);
}

void UStructureDetails::Edit(const FText& InName)
{
	AStructurePart* Section = Cast<AStructurePart>(GetWorld()->SpawnActor(EditClass));
	Section->GetSlot(InName)->TryAttach(EditSlot);
	
	EditSlot = nullptr;
	EditClass = nullptr;
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
		EditSlot = nullptr;
		EditClass = nullptr;
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
	
	NewStructure->LoadLayout(SavedLayout);
	
	AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	if(IsValid(Controller) && Controller->GetPawn() == TargetStructure)
	{
		Controller->Possess(NewStructure);
	}

	TargetStructure->TryDestroy();
	
	DeactivateWidget();
}
