// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/BuildUI/StructurePartInfo.h"
#include "CommonListView.h"
#include "CommonTextBlock.h"
#include "GameplayEffect.h"
#include "Gameplay/Attributes/IntegrityAttributeSet.h"
#include "Gameplay/Attributes/LayoutAttributeSet.h"
#include "Structures/StructureController.h"
#include "Structures/StructurePart.h"
#include "Structures/StructureSlot.h"
#include "UI/Screens/BuildUI/StructureCard.h"
#include "UI/Widgets/Visuals/InfoField.h"

void UStructurePartInfo::NativeConstruct()
{
	Super::NativeConstruct();

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
				if(Modifier.Attribute == UIntegrityAttributeSet::GetMaxIntegrityAttribute()) Hull += Magnitude;
				else if(Modifier.Attribute == ULayoutAttributeSet::GetUpkeepAttribute()) Upkeep += Magnitude;
			}
		}
	}

	HullField->SetContentFromFloat(Hull);
	UpkeepField->SetContentFromFloat(Upkeep);

	RebuildList();
}

void UStructurePartInfo::RebuildList() const
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

void UStructurePartInfo::OnLayoutChanged() const
{
	RebuildList();
}
