// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Flight/Selectors/SelectorCanvas.h"
#include "Algo/RemoveIf.h"
#include "Components/CanvasPanel.h"
#include "Libraries/GameFunctionLibrary.h"
#include "Structures/Structure.h"
#include "UI/Screens/Flight/Selectors/Selector.h"

void USelectorCanvas::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Remove invalid targets
	Targets.SetNum(Algo::RemoveIf(Targets, &ShouldRemove));

	// Remove invalid selectors
	AStructure* Player = UGameFunctionLibrary::GetPlayerStructure(this);
	TArray<TObjectPtr<UTargetable>> Current;
	Selectors.GetKeys(Current);
	for(const TObjectPtr<UTargetable>& Target : Current)
	{
		if(!IsValid(Player) || !IsValid(Target) || !Target->IsTargetable(Player))
		{
			Panel->RemoveChild(Selectors[Target]);
			Selectors.Remove(Target);
		}
	}

	// Add new selectors
	for(const TObjectPtr<UTargetable>& Target : Targets)
	{
		if(IsValid(Player) && Target->IsTargetable(Player) && !Selectors.Contains(Target))
		{
			GUARD_SKIP(IsValid(Target->GetSelectorClass()));
			USelector* Selector = CreateWidget<USelector>(this, Target->GetSelectorClass());
			GUARD_SKIP(IsValid(Selector));
			Selector->Init(Target);
			Panel->AddChildToCanvas(Selector);
			Selectors.Add(Target, Selector);
		}
	}

	// Manually update selectors as they do not tick by themselves when hidden
	for(const TPair<TObjectPtr<UTargetable>, TObjectPtr<USelector>>& Pair : Selectors)
	{
		Pair.Value->Update(MyGeometry);
	}
}

void USelectorCanvas::SetTargets(const TSet<TObjectPtr<UTargetable>>& InTargets)
{
	Targets = InTargets.Array();
}

bool USelectorCanvas::ShouldRemove(const TObjectPtr<UTargetable>& Target)
{
	return !IsValid(Target);
}
