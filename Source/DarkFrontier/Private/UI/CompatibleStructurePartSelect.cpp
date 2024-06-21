// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CompatibleStructurePartSelect.h"
#include "CommonButtonBase.h"
#include "CommonListView.h"
#include "UI/StructureBuilder.h"
#include "Structures/StructurePart.h"
#include "Structures/StructureSlot.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"
#include "UI/CompatibleStructurePartEntryObject.h"

void UCompatibleStructurePartSelect::NativeConstruct()
{
	Super::NativeConstruct();

	StructureBuilder = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UStructureBuilder>(this);

	CloseButton->OnClicked().Clear();
	CloseButton->OnClicked().AddUObject<UCompatibleStructurePartSelect>(this, &UCompatibleStructurePartSelect::OnCloseButtonClicked);
}

void UCompatibleStructurePartSelect::UpdateView() const
{
	TypeList->ClearListItems();
	if(const UStructureSlot* PartSlot = StructureBuilder->GetSelectedSlot())
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
	StructureBuilder->SetSelectedSlot(nullptr);
}
