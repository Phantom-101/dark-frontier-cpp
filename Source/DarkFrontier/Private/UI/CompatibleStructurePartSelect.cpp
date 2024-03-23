// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CompatibleStructurePartSelect.h"
#include "CommonButtonBase.h"
#include "CommonListView.h"
#include "UI/StructureBuilder.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartSlot.h"
#include "Libraries/UIBlueprintLibrary.h"
#include "UI/CompatibleStructurePartEntryObject.h"

void UCompatibleStructurePartSelect::NativeConstruct()
{
	Super::NativeConstruct();

	StructureBuilder = UUIBlueprintLibrary::GetParentWidgetOfClass<UStructureBuilder>(this);

	CloseButton->OnClicked().Clear();
	CloseButton->OnClicked().AddUObject<UCompatibleStructurePartSelect>(this, &UCompatibleStructurePartSelect::OnCloseButtonClicked);
}

void UCompatibleStructurePartSelect::UpdateView() const
{
	TypeList->ClearListItems();
	if(const UStructurePartSlot* PartSlot = StructureBuilder->GetSelectedPartSlot())
	{
		for(TSubclassOf<AStructurePart> Type : StructureBuilder->GetAvailableParts())
		{
			AStructurePart* Part = Cast<AStructurePart>(GetWorld()->SpawnActor(Type));
			if(Part->GetCompatibleSlots(PartSlot).Num() > 0)
			{
				UCompatibleStructurePartEntryObject* Obj = NewObject<UCompatibleStructurePartEntryObject>();
				Obj->Init(Part);
				TypeList->AddItem(Obj);
			}
			Part->Destroy();
		}
	}
	TypeList->RegenerateAllEntries();
	TypeList->ScrollIndexIntoView(0);
}

void UCompatibleStructurePartSelect::OnCloseButtonClicked() const
{
	StructureBuilder->SetSelectedPartSlot(nullptr);
}
