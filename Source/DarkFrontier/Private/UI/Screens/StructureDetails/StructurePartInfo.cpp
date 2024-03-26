// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/StructureDetails/StructurePartInfo.h"
#include "CommonListView.h"
#include "CommonTextBlock.h"
#include "GameplayEffect.h"
#include "Structures/StructureAttributeSet.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartSlot.h"
#include "UI/Widgets/InfoField.h"
#include "UI/Screens/StructureDetails/StructureCard.h"

void UStructurePartInfo::SetTarget(AStructurePart* InTargetPart)
{
	TargetPart = InTargetPart;

	TypeText->SetText(TargetPart->TypeName);
	StructureCard->SetTarget(TargetPart->OwningStructure);
	
	float Hull = 0;
	float Upkeep = 0;

	if(TargetPart->PassiveEffect != nullptr)
	{
		UGameplayEffect* Effect = TargetPart->PassiveEffect->GetDefaultObject<UGameplayEffect>();
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

	SlotCardList->ClearListItems();
	for(UStructurePartSlot* PartSlot : TargetPart->Slots)
	{
		SlotCardList->AddItem(PartSlot);
	}
	SlotCardList->RegenerateAllEntries();
	SlotCardList->ScrollIndexIntoView(0);
}
