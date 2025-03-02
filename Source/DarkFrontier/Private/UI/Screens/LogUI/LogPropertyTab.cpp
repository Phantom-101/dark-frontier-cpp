// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/LogUI/LogPropertyTab.h"
#include "CommonButtonBase.h"
#include "EngineUtils.h"
#include "Components/WidgetSwitcher.h"
#include "Factions/Faction.h"
#include "Structures/Structure.h"
#include "UI/Screens/LogUI/PropertyInfo.h"
#include "UI/Screens/LogUI/StructureEntry.h"
#include "UI/Widgets/Interaction/ListBox.h"

void ULogPropertyTab::NativeConstruct()
{
	Super::NativeConstruct();

	const AFaction* PlayerFaction = Cast<AStructure>(GetWorld()->GetFirstPlayerController()->GetPawn())->GetOwningFaction();
	
	TArray<UObject*> Structures;
	for(TActorIterator<AStructure> Itr(GetWorld()); Itr; ++Itr)
	{
		if(Itr->GetOwningFaction() == PlayerFaction)
		{
			Structures.Add(*Itr);
		}
	}
	
	StructureListBox->SetOptions(TArray<UObject*>(Structures));
	StructureListBox->SetBuilder([Owner = this, Class = EntryClass](UObject* Faction)
	{
		UStructureEntry* Option = CreateWidget<UStructureEntry>(Owner, Class);
		Option->Init(Cast<AStructure>(Faction));
		return Option;
	});

	StructureListBox->OnChanged.AddUObject<ULogPropertyTab>(this, &ULogPropertyTab::HandleSelect);
	BackButton->OnClicked().AddUObject<ULogPropertyTab>(this, &ULogPropertyTab::HandleBack);
}

void ULogPropertyTab::HandleSelect(UObject* Object) const
{
	if(Object == nullptr)
	{
		Switcher->SetActiveWidgetIndex(0);
	}
	else
	{
		Switcher->SetActiveWidgetIndex(1);
		PropertyInfo->Init(Cast<AStructure>(Object));
	}
}

void ULogPropertyTab::HandleBack() const
{
	StructureListBox->SetCurrentOption(nullptr);
}
