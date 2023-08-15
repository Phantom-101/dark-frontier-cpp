// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CompatibleSectionSelect.h"
#include "CommonButtonBase.h"
#include "CommonListView.h"
#include "UI/StructureBuilder.h"
#include "Structures/StructureSection.h"
#include "Structures/StructureSectionSlot.h"
#include "Libraries/UIBlueprintLibrary.h"
#include "UI/CompatibleSectionEntryObject.h"

void UCompatibleSectionSelect::NativeConstruct()
{
	Super::NativeConstruct();

	StructureBuilder = UUIBlueprintLibrary::GetParentWidgetOfClass<UStructureBuilder>(this);

	CloseButton->OnClicked().AddUObject<UCompatibleSectionSelect>(this, &UCompatibleSectionSelect::OnCloseButtonClicked);
}

void UCompatibleSectionSelect::UpdateView() const
{
	TypeList->ClearListItems();
	if(const UStructureSectionSlot* SectionSlot = StructureBuilder->GetSelectedSectionSlot())
	{
		for(TSubclassOf<AStructureSection> Type : StructureBuilder->GetAvailableSectionTypes())
		{
			AStructureSection* Section = Cast<AStructureSection>(GetWorld()->SpawnActor(Type));
			if(Section->GetCompatibleSectionSlots(SectionSlot->SlotType).Num() > 0)
			{
				UCompatibleSectionEntryObject* Obj = NewObject<UCompatibleSectionEntryObject>();
				Obj->Init(Section);
				TypeList->AddItem(Obj);
			}
			Section->Destroy();
		}
	}
	TypeList->RegenerateAllEntries();
}

void UCompatibleSectionSelect::OnCloseButtonClicked() const
{
	StructureBuilder->SetSelectedSectionSlot(nullptr);
}
