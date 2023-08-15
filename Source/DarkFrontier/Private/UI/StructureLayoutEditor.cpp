// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/StructureLayoutEditor.h"
#include "CommonListView.h"
#include "Structures/Structure.h"
#include "Structures/StructureSection.h"

void UStructureLayoutEditor::UpdateView(AStructure* Target)
{
	Sections->ClearListItems();
	for(AStructureSection* Section : Target->GetCachedSections())
	{
		Sections->AddItem(Section);
	}
	Sections->RegenerateAllEntries();
	Sections->RequestRefresh();
}
