// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/StructureSelector.h"
#include "Structures/Structure.h"

void UStructureSelector::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	AStructure* Player = Cast<AStructure>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(IsValid(Player))
	{
		if(Target == Player)
		{
			SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
	}
}
