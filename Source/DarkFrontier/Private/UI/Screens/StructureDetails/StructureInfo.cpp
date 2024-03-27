// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructureInfo.h"
#include "AbilitySystemComponent.h"
#include "CommonButtonBase.h"
#include "CommonListView.h"
#include "CommonTextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"
#include "Structures/Structure.h"
#include "Structures/StructureAttributeSet.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartSlot.h"
#include "Structures/StructurePartSlotType.h"
#include "UI/Screens/StructureDetails/StructurePartSlotListView.h"
#include "UI/Widgets/InfoField.h"

void UStructureInfo::NativeConstruct()
{
	Super::NativeConstruct();

	TypeModeButton->OnClicked().Clear();
	TypeModeButton->OnClicked().AddUObject<UStructureInfo>(this, &UStructureInfo::TypeModeSelected);

	ListModeButton->OnClicked().Clear();
	ListModeButton->OnClicked().AddUObject<UStructureInfo>(this, &UStructureInfo::ListModeSelected);
}

void UStructureInfo::SetTarget(AStructure* InTargetStructure)
{
	TargetStructure = InTargetStructure;

	NameText->SetText(FText::FromString(TargetStructure->GetName()));
	
	const UAbilitySystemComponent* AbilitySystemComp = TargetStructure->GetAbilitySystemComponent();
	const UStructureAttributeSet* Attributes = Cast<UStructureAttributeSet>(AbilitySystemComp->GetAttributeSet(UStructureAttributeSet::StaticClass()));

	const float MaxHull = Attributes->GetMaxHull();
	const float MaxShield = Attributes->GetMaxShield();
	const float ShieldRegen = Attributes->GetShieldRegen();
	const float MaxEnergy = Attributes->GetMaxEnergy();
	const float EnergyRegen = Attributes->GetEnergyRegen();
	const float MaxUpkeep = Attributes->GetMaxUpkeep();
	const float Upkeep = Attributes->GetUpkeep() / Attributes->GetUpkeepReduction();
	const float LinearSpeed = Attributes->GetLinearMaxSpeed();
	const float LinearAccel = Attributes->GetLinearAcceleration();
	const float AngularSpeed = Attributes->GetAngularMaxSpeed();
	const float AngularAccel = Attributes->GetAngularAcceleration();
	
	TArray<FStringFormatArg> FormatArgs;
	
	HullField->SetContentFromFloat(MaxHull);
	
	FormatArgs.Add(FStringFormatArg(ToString(MaxShield)));
	FormatArgs.Add(FStringFormatArg(ToString(ShieldRegen)));
	ShieldField->SetContentFromString(FString::Format(TEXT("{0}+{1}"), FormatArgs));
	
	FormatArgs.Empty();
	FormatArgs.Add(FStringFormatArg(ToString(MaxEnergy)));
	FormatArgs.Add(FStringFormatArg(ToString(EnergyRegen)));
	EnergyField->SetContentFromString(FString::Format(TEXT("{0}+{1}"), FormatArgs));

	FormatArgs.Empty();
	FormatArgs.Add(FStringFormatArg(ToString(Upkeep)));
	FormatArgs.Add(FStringFormatArg(ToString(MaxUpkeep)));
	UpkeepField->SetContentFromString(FString::Format(TEXT("{0}/{1}"), FormatArgs));
	
	FormatArgs.Empty();
	FormatArgs.Add(FStringFormatArg(ToString(LinearSpeed)));
	FormatArgs.Add(FStringFormatArg(ToString(LinearAccel)));
	LinearField->SetContentFromString(FString::Format(TEXT("{0}+{1}"), FormatArgs));
	
	FormatArgs.Empty();
	FormatArgs.Add(FStringFormatArg(ToString(AngularSpeed)));
	FormatArgs.Add(FStringFormatArg(ToString(AngularAccel)));
	AngularField->SetContentFromString(FString::Format(TEXT("{0}+{1}"), FormatArgs));

	TypeModeSelected();
}

void UStructureInfo::TypeModeSelected()
{
	TypeModeButton->SetStyle(SelectedStyle);
	ListModeButton->SetStyle(UnSelectedStyle);

	PartListSwitcher->SetActiveWidget(TypeList);

	TypeList->ClearChildren();
	TArray<UStructurePartSlotType*> SlotTypes;
	for(AStructurePart* Part : TargetStructure->GetParts())
	{
		for(const UStructurePartSlot* PartSlot : Part->GetSlots())
		{
			if(!SlotTypes.Contains(PartSlot->GetSlotType()))
			{
				SlotTypes.Add(PartSlot->GetSlotType());
			}
		}
	}
	for(UStructurePartSlotType* SlotType : SlotTypes)
	{
		UStructurePartSlotListView* View = CreateWidget<UStructurePartSlotListView>(this, ListViewClass);
		TypeList->AddChild(View);
		View->Init(TargetStructure, SlotType);
	}
}

void UStructureInfo::ListModeSelected()
{
	TypeModeButton->SetStyle(UnSelectedStyle);
	ListModeButton->SetStyle(SelectedStyle);

	PartListSwitcher->SetActiveWidget(PartCardList);

	PartCardList->ClearListItems();
	for(AStructurePart* Part : TargetStructure->GetParts())
	{
		PartCardList->AddItem(Part);
	}
	PartCardList->RegenerateAllEntries();
	PartCardList->ScrollIndexIntoView(0);
}

FString UStructureInfo::ToString(const float Value)
{
	return FString::FromInt(FMath::RoundToInt(Value));
}

FText UStructureInfo::ToText(const FString& String)
{
	return FText::FromString(String);
}
