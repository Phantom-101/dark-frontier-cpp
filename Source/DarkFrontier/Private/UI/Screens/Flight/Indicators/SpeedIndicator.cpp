// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Flight/Indicators/SpeedIndicator.h"
#include "CommonTextBlock.h"
#include "Libraries/GameFunctionLibrary.h"
#include "Structures/Structure.h"
#include "Structures/Indications/SpeedIndication.h"

void USpeedIndicator::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	const USpeedIndication* Speed = Cast<USpeedIndication>(Indication);
	const bool IsSelected = UGameFunctionLibrary::IsSelected(TScriptInterface<ITargetable>(Speed->GetStructure()));
	SpeedText->SetVisibility(IsSelected ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
	SpeedText->SetText(FText::FromString(FString::Printf(TEXT("%d m/s"), FMath::RoundToInt(Speed->GetSpeed() / 100))));
}
