// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Flight/Indicators/DistanceIndicator.h"
#include "CommonTextBlock.h"
#include "Libraries/GameFunctionLibrary.h"
#include "Structures/Structure.h"
#include "Structures/Indications/DistanceIndication.h"

void UDistanceIndicator::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	const UDistanceIndication* Distance = Cast<UDistanceIndication>(Indication);
	const bool IsSelected = UGameFunctionLibrary::IsSelected(TScriptInterface<ITargetable>(Distance->GetStructure()));
	DistanceText->SetVisibility(IsSelected ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
	DistanceText->SetText(FText::FromString(FString::Printf(TEXT("%d m"), FMath::RoundToInt(Distance->GetDistance() / 100))));
}
