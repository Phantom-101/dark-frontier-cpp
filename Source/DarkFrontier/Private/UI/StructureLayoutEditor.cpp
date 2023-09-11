// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/StructureLayoutEditor.h"
#include "CommonListView.h"
#include "Structures/Structure.h"
#include "Structures/StructurePart.h"

void UStructureLayoutEditor::UpdateView(AStructure* Target) const
{
	Parts->ClearListItems();
	for(AStructurePart* Part : Target->GetCachedParts())
	{
		Parts->AddItem(Part);
	}
	Parts->RegenerateAllEntries();
	Parts->RequestRefresh();
}
