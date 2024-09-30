// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructureInfo.h"
#include "AbilitySystemComponent.h"
#include "CommonButtonBase.h"
#include "CommonListView.h"
#include "CommonTextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"
#include "Gameplay/Attributes/EnergyAttributeSet.h"
#include "Gameplay/Attributes/IntegrityAttributeSet.h"
#include "Gameplay/Attributes/LayoutAttributeSet.h"
#include "Structures/Structure.h"
#include "Structures/StructureAttributeSet.h"
#include "Structures/StructureController.h"
#include "Structures/StructureGameplay.h"
#include "Structures/StructureIndices.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartGroup.h"
#include "UI/Screens/StructureDetails/StructurePartCardList.h"
#include "UI/Widgets/InfoField.h"

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
	
	const UAbilitySystemComponent* AbilitySystemComp = TargetStructure->GetAbilitySystemComponent();
	const UStructureAttributeSet* Attributes = Cast<UStructureAttributeSet>(AbilitySystemComp->GetAttributeSet(UStructureAttributeSet::StaticClass()));

	UStructureGameplay* Gameplay = TargetStructure->GetGameplay();
	
	const float MaxHull = Gameplay->GetMaxIntegrity();
	// TODO replace with actual shield
	const float MaxShield = Gameplay->GetMaxIntegrity();
	const float ShieldRegen = 0;
	const float MaxEnergy = Gameplay->GetMaxEnergy();
	const float EnergyRegen = Gameplay->GetEnergyRegeneration();
	const float MaxUpkeep = Gameplay->GetMaxUpkeep();
	const float Upkeep = Gameplay->GetUpkeep();
	const float LinearSpeed = Attributes->GetLinearMaxSpeed();
	const float LinearAccel = Attributes->GetLinearAcceleration();
	const float AngularSpeed = Attributes->GetAngularMaxSpeed();
	const float AngularAccel = Attributes->GetAngularAcceleration();
	
	TArray<FStringFormatArg> FormatArgs;
	
	HullField->SetContentFromFloat(MaxHull);
	ShieldField->SetContentFromString(FString::Printf(TEXT("%g+%g"), MaxShield, ShieldRegen));
	EnergyField->SetContentFromString(FString::Printf(TEXT("%g+%g"), MaxEnergy, EnergyRegen));
	UpkeepField->SetContentFromString(FString::Printf(TEXT("%g/%g"), Upkeep, MaxUpkeep));
	LinearField->SetContentFromString(FString::Printf(TEXT("%g+%g"), LinearSpeed, LinearAccel));
	AngularField->SetContentFromString(FString::Printf(TEXT("%g+%g"), AngularSpeed, AngularAccel));

	OnTypeModeSelected();
	RebuildTypeMode();
	RebuildListMode();
}

void UStructureInfo::RebuildTypeMode()
{
	if(!IsValid(TargetStructure)) return;
	
	TArray<UStructurePartGroup*> PartTypes;
	for(const AStructurePart* Part : TargetStructure->GetIndices()->GetParts())
	{
		PartTypes.AddUnique(Part->GetPartType());
	}

	TypeList->ClearChildren();
	for(const UStructurePartGroup* PartType : PartTypes)
	{
		TArray<AStructurePart*> Parts;
		for(AStructurePart* Part : TargetStructure->GetIndices()->GetParts())
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
	for(AStructurePart* Part : TargetStructure->GetIndices()->GetParts())
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
