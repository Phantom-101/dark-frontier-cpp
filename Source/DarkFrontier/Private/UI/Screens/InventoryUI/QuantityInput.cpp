// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/InventoryUI/QuantityInput.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/Slider.h"

void UQuantityInput::NativePreConstruct()
{
	Super::NativePreConstruct();

	QuantitySlider->SetMinValue(0);
	QuantitySlider->SetMaxValue(MaxQuantity);
	QuantitySlider->SetValue(CurrentQuantity);
}

void UQuantityInput::NativeConstruct()
{
	Super::NativeConstruct();

	QuantitySlider->OnValueChanged.Clear();
	QuantitySlider->OnValueChanged.AddDynamic(this, &UQuantityInput::HandleSlider);
	AddOneButton->OnClicked().Clear();
	AddOneButton->OnClicked().AddUObject<UQuantityInput>(this, &UQuantityInput::HandleAddOne);
	AddTenButton->OnClicked().Clear();
	AddTenButton->OnClicked().AddUObject<UQuantityInput>(this, &UQuantityInput::HandleAddTen);
	AddAllButton->OnClicked().Clear();
	AddAllButton->OnClicked().AddUObject<UQuantityInput>(this, &UQuantityInput::HandleAddAll);
	RemoveOneButton->OnClicked().Clear();
	RemoveOneButton->OnClicked().AddUObject<UQuantityInput>(this, &UQuantityInput::HandleRemoveOne);
	RemoveTenButton->OnClicked().Clear();
	RemoveTenButton->OnClicked().AddUObject<UQuantityInput>(this, &UQuantityInput::HandleRemoveTen);
	RemoveAllButton->OnClicked().Clear();
	RemoveAllButton->OnClicked().AddUObject<UQuantityInput>(this, &UQuantityInput::HandleRemoveAll);
}

int UQuantityInput::GetMaxQuantity() const
{
	return MaxQuantity;
}

void UQuantityInput::SetMaxQuantity(const int InMax)
{
	MaxQuantity = InMax;
	QuantitySlider->SetMaxValue(MaxQuantity);
	SetQuantity(CurrentQuantity);
}

int UQuantityInput::GetQuantity() const
{
	return CurrentQuantity;
}

void UQuantityInput::SetQuantity(const int Target)
{
	const int Clamped = FMath::Clamp(Target, 0, MaxQuantity);
	CurrentQuantity = Clamped;
	QuantityText->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), CurrentQuantity, MaxQuantity)));
	QuantitySlider->SetValue(CurrentQuantity);
}

void UQuantityInput::HandleSlider(const float Value)
{
	SetQuantity(FMath::RoundToInt(Value));
}

void UQuantityInput::HandleAddOne()
{
	SetQuantity(CurrentQuantity + 1);
}

void UQuantityInput::HandleAddTen()
{
	SetQuantity(CurrentQuantity + 10);
}

void UQuantityInput::HandleAddAll()
{
	SetQuantity(MaxQuantity);
}

void UQuantityInput::HandleRemoveOne()
{
	SetQuantity(CurrentQuantity - 1);
}

void UQuantityInput::HandleRemoveTen()
{
	SetQuantity(CurrentQuantity - 10);
}

void UQuantityInput::HandleRemoveAll()
{
	SetQuantity(0);
}
