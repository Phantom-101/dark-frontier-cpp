// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/ClickableCard.h"

#include "CommonBorder.h"
#include "CommonButtonBase.h"

void UClickableCard::NativePreConstruct()
{
	Super::NativePreConstruct();

	Border->SetStyle(Style);
}

void UClickableCard::NativeConstruct()
{
	Super::NativeConstruct();

	ClickArea->OnClicked().Clear();
	ClickArea->OnClicked().AddUObject<UClickableCard>(this, &UClickableCard::OnCardClicked);
}

void UClickableCard::OnCardClicked() const
{
	if(OnClicked.IsBound())
	{
		OnClicked.Execute();
	}
}
