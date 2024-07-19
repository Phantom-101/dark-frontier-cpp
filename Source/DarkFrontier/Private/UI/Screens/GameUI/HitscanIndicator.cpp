// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/HitscanIndicator.h"
#include "Components/SizeBox.h"
#include "Structures/HitscanIndication.h"
#include "Structures/Structure.h"

void UHitscanIndicator::NativePreConstruct()
{
	Super::NativePreConstruct();

	if(IsValid(SizeBox))
	{
		SizeBox->SetWidthOverride(MaxSize);
		SizeBox->SetHeightOverride(MaxSize);
	}
}

void UHitscanIndicator::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UHitscanIndication* HitscanIndication = Cast<UHitscanIndication>(Indication);

	HitscanIndication->CurrentTime -= InDeltaTime;

	const float Multiplier = FMath::Clamp(HitscanIndication->CurrentTime / HitscanIndication->MaxTime, 0, 1);

	if(Multiplier == 0)
	{
		HitscanIndication->GetStructure()->RemoveIndication(HitscanIndication);
	}
	else
	{
		SizeBox->SetWidthOverride(MaxSize * Multiplier);
		SizeBox->SetHeightOverride(MaxSize * Multiplier);
	}
}
