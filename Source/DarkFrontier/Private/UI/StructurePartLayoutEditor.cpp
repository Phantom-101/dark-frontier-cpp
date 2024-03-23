// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/StructurePartLayoutEditor.h"
#include "CommonListView.h"
#include "CommonTextBlock.h"
#include "Structures/StructurePart.h"
#include "Structures/Structure.h"
#include "Structures/StructurePartSlot.h"

void UStructurePartLayoutEditor::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	const AStructurePart* Part = Cast<AStructurePart>(ListItemObject);

	TypeText->SetText(Part->TypeName);
	IdText->SetText(FText::FromString(FString::Printf(TEXT("#%i"), Part->PartId)));
	RootSectionText->SetVisibility(Part == Part->OwningStructure->GetRootPart() ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);

	PartSlotList->ClearListItems();
	for(UStructurePartSlot* PartSlot : Part->PartSlots)
	{
		PartSlotList->AddItem(PartSlot);
	}
	PartSlotList->RegenerateAllEntries();
	PartSlotList->ScrollIndexIntoView(0);
}
