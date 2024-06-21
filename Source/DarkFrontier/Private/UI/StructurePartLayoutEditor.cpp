// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/StructurePartLayoutEditor.h"
#include "CommonListView.h"
#include "CommonTextBlock.h"
#include "Structures/StructurePart.h"
#include "Structures/Structure.h"
#include "Structures/StructureSlot.h"

void UStructurePartLayoutEditor::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	AStructurePart* Part = Cast<AStructurePart>(ListItemObject);

	TypeText->SetText(Part->GetTypeName());
	IdText->SetText(FText::FromString(FString::Printf(TEXT("%s"), *Part->GetPartId())));
	RootSectionText->SetVisibility(Part == Part->GetOwningStructure()->GetRootPart() ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);

	PartSlotList->ClearListItems();
	for(UStructureSlot* PartSlot : Part->GetSlots())
	{
		PartSlotList->AddItem(PartSlot);
	}
	PartSlotList->RegenerateAllEntries();
	PartSlotList->ScrollIndexIntoView(0);
}
