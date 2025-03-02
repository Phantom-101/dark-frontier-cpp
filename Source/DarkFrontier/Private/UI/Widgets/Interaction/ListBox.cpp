// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Interaction/ListBox.h"
#include "CommonListView.h"
#include "UI/Widgets/Visuals/ListBoxOptionParams.h"

TArray<UObject*> UListBox::GetOptions() const
{
	return Options;
}

void UListBox::SetOptions(const TArray<UObject*>& InOptions)
{
	Options = InOptions;
	if(!Options.Contains(CurrentOption))
	{
		SetCurrentOption(nullptr);
	}
}

void UListBox::SetOptionsWithInitial(const TArray<UObject*>& InOptions, UObject* Initial)
{
	Options = InOptions;
	SetCurrentOption(Initial);
}

void UListBox::SetCurrentOption(UObject* Option)
{
	if(Option == nullptr || Options.Contains(Option))
	{
		CurrentOption = Option;
		OnChanged.Broadcast(CurrentOption);
	}
}

void UListBox::SetBuilder(const TFunction<UWidget*(UObject*)>& Builder)
{
	OptionBuilder = Builder;
	Rebuild();
}

bool UListBox::IsCurrentOptionValid() const
{
	return Options.Contains(CurrentOption);
}

UObject* UListBox::GetCurrentOption()
{
	return CurrentOption;
}

void UListBox::Rebuild()
{
	OptionList->ClearListItems();
	for(UObject* Option : Options)
	{
		UListBoxOptionParams* Params = NewObject<UListBoxOptionParams>();
		Params->ListBox = this;
		Params->Option = Option;
		Params->Builder = OptionBuilder;
		OptionList->AddItem(Params);
	}
	OptionList->RegenerateAllEntries();
}
