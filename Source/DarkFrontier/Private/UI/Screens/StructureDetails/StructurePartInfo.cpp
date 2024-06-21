// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructurePartInfo.h"
#include "CommonButtonBase.h"
#include "CommonListView.h"
#include "CommonTextBlock.h"
#include "GameplayEffect.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"
#include "Structures/StructureAttributeSet.h"
#include "Structures/StructureController.h"
#include "Structures/StructurePart.h"
#include "Structures/StructureSlot.h"
#include "Structures/StructureSlotType.h"
#include "UI/Widgets/InfoField.h"
#include "UI/Screens/StructureDetails/StructureCard.h"
#include "UI/Screens/StructureDetails/StructureSlotCardList.h"

void UStructurePartInfo::NativeConstruct()
{
	Super::NativeConstruct();

	TypeModeButton->OnClicked().Clear();
	TypeModeButton->OnClicked().AddUObject<UStructurePartInfo>(this, &UStructurePartInfo::OnTypeModeSelected);

	ListModeButton->OnClicked().Clear();
	ListModeButton->OnClicked().AddUObject<UStructurePartInfo>(this, &UStructurePartInfo::OnListModeSelected);

	AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	if(IsValid(Controller))
	{
		if(!OnLayoutChangedHandle.IsValid())
		{
			OnLayoutChangedHandle = Controller->OnLayoutChanged.AddUObject<UStructurePartInfo>(this, &UStructurePartInfo::OnLayoutChanged);
		}
	}
}

AStructurePart* UStructurePartInfo::GetTarget() const
{
	return TargetPart;
}

void UStructurePartInfo::SetTarget(AStructurePart* InTargetPart)
{
	TargetPart = InTargetPart;

	TypeText->SetText(TargetPart->GetTypeName());
	StructureCard->SetTarget(TargetPart->GetOwningStructure());
	
	float Hull = 0;
	float Upkeep = 0;

	if(TargetPart->GetPassiveEffect())
	{
		UGameplayEffect* Effect = TargetPart->GetPassiveEffect()->GetDefaultObject<UGameplayEffect>();
		for(FGameplayModifierInfo Modifier : Effect->Modifiers)
		{
			float Magnitude;
			if(Modifier.ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Magnitude))
			{
				if(Modifier.Attribute == UStructureAttributeSet::GetMaxHullAttribute()) Hull += Magnitude;
				else if(Modifier.Attribute == UStructureAttributeSet::GetUpkeepAttribute()) Upkeep += Magnitude;
			}
		}
	}

	HullField->SetContentFromFloat(Hull);
	UpkeepField->SetContentFromFloat(Upkeep);

	OnTypeModeSelected();
	RebuildTypeMode();
	RebuildListMode();
}

void UStructurePartInfo::RebuildTypeMode()
{
	if(!IsValid(TargetPart)) return;
	
	// Collate slots
	TMap<UStructureSlotType*, TArray<UStructureSlot*>> TypeMap;
	TArray<UStructureSlot*> MiscSlots;
	for(UStructureSlot* PartSlot : TargetPart->GetSlots())
	{
		if(!PartSlot->GetSlotType())
		{
			MiscSlots.Add(PartSlot);
			continue;
		}
			
		if(!TypeMap.Contains(PartSlot->GetSlotType()))
		{
			TypeMap.Add(PartSlot->GetSlotType(), TArray<UStructureSlot*>());
		}
		TypeMap[PartSlot->GetSlotType()].Add(PartSlot);
	}

	// Add to list
	TypeList->ClearChildren();
	for(const TPair<UStructureSlotType*, TArray<UStructureSlot*>> Pair : TypeMap)
	{
		UStructureSlotCardList* View = CreateWidget<UStructureSlotCardList>(this, CardListClass);
		TypeList->AddChild(View);
		View->Init(Pair.Value, Pair.Key->TypeName, Pair.Key->Color);
	}
	
	if(MiscSlots.Num() > 0)
	{
		UStructureSlotCardList* View = CreateWidget<UStructureSlotCardList>(this, CardListClass);
		TypeList->AddChild(View);
		View->Init(MiscSlots, FText::FromString("Miscellaneous"), FLinearColor::White);
	}
}

void UStructurePartInfo::RebuildListMode() const
{
	if(!IsValid(TargetPart)) return;
	
	SlotCardList->ClearListItems();
	for(UStructureSlot* PartSlot : TargetPart->GetSlots())
	{
		SlotCardList->AddItem(PartSlot);
	}
	SlotCardList->RegenerateAllEntries();
	// We don't need to scroll the first item into view as all elements are of fixed height
}

void UStructurePartInfo::OnTypeModeSelected() const
{
	TypeModeButton->SetStyle(SelectedStyle);
	ListModeButton->SetStyle(UnSelectedStyle);

	SlotListSwitcher->SetActiveWidget(TypeList);
}

void UStructurePartInfo::OnListModeSelected() const
{
	TypeModeButton->SetStyle(UnSelectedStyle);
	ListModeButton->SetStyle(SelectedStyle);

	SlotListSwitcher->SetActiveWidget(SlotCardList);
}

void UStructurePartInfo::OnLayoutChanged()
{
	RebuildTypeMode();
	RebuildListMode();
}
