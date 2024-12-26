// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Interaction/CycleButton.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"

void UCycleButton::NativeConstruct()
{
	Super::NativeConstruct();

	LeftButton->OnClicked().Clear();
	LeftButton->OnClicked().AddUObject<UCycleButton>(this, &UCycleButton::SelectLeft);
	RightButton->OnClicked().Clear();
	RightButton->OnClicked().AddUObject<UCycleButton>(this, &UCycleButton::SelectRight);

	SetSelected(0);
}

void UCycleButton::SetOptions(const TArray<FText>& InOptions)
{
	Options = InOptions;

	SetSelected(0);
}

void UCycleButton::SelectLeft()
{
	if(Options.Num() > 0)
	{
		SetSelected(GetBounded(SelectedIndex - 1));
	}
}

void UCycleButton::SelectRight()
{
	if(Options.Num() > 0)
	{
		SetSelected(GetBounded(SelectedIndex + 1));
	}
}

void UCycleButton::SetSelected(const int Target)
{
	SelectedIndex = GetBounded(Target);

	if(Options.Num() == 0)
	{
		OptionText->SetText(FText::FromString("None"));
	}
	else
	{
		OptionText->SetText(Options[SelectedIndex]);

		OnOptionSelected.Broadcast(SelectedIndex);
	}
}

int UCycleButton::GetBounded(const int Target) const
{
	if(Options.Num() == 0)
	{
		return 0;
	}

	const int FloorQuotient = Target >= 0 ? Target / Options.Num() : (Target - Options.Num() + 1) / Options.Num();
	return Target - FloorQuotient * Options.Num();
}
