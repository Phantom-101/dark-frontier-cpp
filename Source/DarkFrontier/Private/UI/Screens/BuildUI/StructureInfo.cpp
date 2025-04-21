// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/BuildUI/StructureInfo.h"
#include "CommonButtonBase.h"
#include "CommonListView.h"
#include "CommonTextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"
#include "Structures/Structure.h"
#include "Structures/StructureController.h"
#include "Structures/StructureGameplay.h"
#include "Structures/StructureLayout.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartGroup.h"
#include "UI/Screens/BuildUI/StructurePartCardList.h"
#include "UI/Widgets/Visuals/InfoField.h"

void UStructureInfo::NativeConstruct()
{
	Super::NativeConstruct();

	TypeModeButton->OnClicked().Clear();
	TypeModeButton->OnClicked().AddUObject<UStructureInfo>(this, &UStructureInfo::OnTypeModeSelected);

	ListModeButton->OnClicked().Clear();
	ListModeButton->OnClicked().AddUObject<UStructureInfo>(this, &UStructureInfo::OnListModeSelected);

	AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController());
	if(IsValid(Controller))
	{
		if(!OnLayoutChangedHandle.IsValid())
		{
			OnLayoutChangedHandle = Controller->OnLayoutChanged.AddUObject<UStructureInfo>(this, &UStructureInfo::OnLayoutChanged);
		}
	}
}

void UStructureInfo::SetTarget(AStructure* InTargetStructure)
{
	TargetStructure = InTargetStructure;

	NameText->SetText(FText::FromString(TargetStructure->GetName()));
	
	UStructureGameplay* Gameplay = TargetStructure->GetGameplay();
	
	const float MaxHull = Gameplay->GetMaxHull();
	const float MaxShield = Gameplay->GetMaxShield();
	const float ShieldRegen = Gameplay->GetShieldRegeneration();
	const float MaxEnergy = Gameplay->GetMaxEnergy();
	const float EnergyRegen = Gameplay->GetEnergyRegeneration();
	const float MaxUpkeep = Gameplay->GetMaxUpkeep();
	const float Upkeep = Gameplay->GetUpkeep();
	const float LinearSpeed = Gameplay->GetLinearMaxSpeed();
	const float LinearAccel = Gameplay->GetLinearAcceleration();
	const float AngularSpeed = Gameplay->GetAngularMaxSpeed();
	const float AngularAccel = Gameplay->GetAngularAcceleration();
	
	TArray<FStringFormatArg> FormatArgs;
	
	HullField->SetContentFromFloat(MaxHull);
	ShieldField->SetContentFromString(FString::Printf(TEXT("%.1f+%.1f"), MaxShield, ShieldRegen));
	EnergyField->SetContentFromString(FString::Printf(TEXT("%.1f+%.1f"), MaxEnergy, EnergyRegen));
	UpkeepField->SetContentFromString(FString::Printf(TEXT("%.1f/%.1f"), Upkeep, MaxUpkeep));
	LinearField->SetContentFromString(FString::Printf(TEXT("%.1f+%.1f"), LinearSpeed, LinearAccel));
	AngularField->SetContentFromString(FString::Printf(TEXT("%.1f+%.1f"), AngularSpeed, AngularAccel));

	OnTypeModeSelected();
	RebuildTypeMode();
	RebuildListMode();
}

void UStructureInfo::RebuildTypeMode()
{
	if(!IsValid(TargetStructure)) return;
	
	TArray<UStructurePartGroup*> PartTypes;
	for(const AStructurePart* Part : TargetStructure->GetLayout()->GetParts())
	{
		PartTypes.AddUnique(Part->GetPartType());
	}

	TypeList->ClearChildren();
	for(const UStructurePartGroup* PartType : PartTypes)
	{
		TArray<AStructurePart*> Parts;
		for(AStructurePart* Part : TargetStructure->GetLayout()->GetParts())
		{
			if(Part->GetPartType() == PartType)
			{
				Parts.Add(Part);
			}
		}
		
		UStructurePartCardList* CardList = CreateWidget<UStructurePartCardList>(this, CardListClass);
		TypeList->AddChild(CardList);

		if(PartType == nullptr)
		{
			CardList->SetHeader(FText::FromString("Miscellaneous"));
			CardList->SetHeaderColor(FLinearColor::White);
		}
		else
		{
			CardList->SetHeader(PartType->TypeName);
			CardList->SetHeaderColor(PartType->Color);
		}

		CardList->SetParts(Parts);
	}
}

void UStructureInfo::RebuildListMode() const
{
	if(!IsValid(TargetStructure)) return;
	
	PartCardList->ClearListItems();
	for(AStructurePart* Part : TargetStructure->GetLayout()->GetParts())
	{
		PartCardList->AddItem(Part);
	}
	PartCardList->RegenerateAllEntries();
	// We don't need to scroll the first item into view as all elements are of fixed height
}

void UStructureInfo::OnTypeModeSelected() const
{
	TypeModeButton->SetStyle(SelectedStyle);
	ListModeButton->SetStyle(UnSelectedStyle);

	PartListSwitcher->SetActiveWidget(TypeList);
}

void UStructureInfo::OnListModeSelected() const
{
	TypeModeButton->SetStyle(UnSelectedStyle);
	ListModeButton->SetStyle(SelectedStyle);

	PartListSwitcher->SetActiveWidget(PartCardList);
}

void UStructureInfo::OnLayoutChanged()
{
	RebuildTypeMode();
	RebuildListMode();
}

FString UStructureInfo::ToString(const float Value)
{
	return FString::FromInt(FMath::RoundToInt(Value));
}

FText UStructureInfo::ToText(const FString& String)
{
	return FText::FromString(String);
}
