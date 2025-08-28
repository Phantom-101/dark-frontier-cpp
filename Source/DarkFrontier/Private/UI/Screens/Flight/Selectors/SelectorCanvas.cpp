// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Flight/Selectors/SelectorCanvas.h"
#include "Algo/RemoveIf.h"
#include "Components/CanvasPanel.h"
#include "Libraries/GameFunctionLibrary.h"
#include "Objects/Targetable.h"
#include "Structures/Structure.h"
#include "UI/Screens/Flight/Selectors/Selector.h"

void USelectorCanvas::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Remove invalid targets
	Targets.SetNum(Algo::RemoveIf(Targets, &ShouldRemove));

	// Remove invalid selectors
	AStructure* Player = UGameFunctionLibrary::GetPlayerStructure(this);
	TArray<TObjectPtr<UObject>> Current;
	Selectors.GetKeys(Current);
	for(const TObjectPtr<UObject>& Target : Current)
	{
		if(!IsValid(Player) || !IsValid(Target) || !Cast<ITargetable>(Target)->IsTargetable(Player))
		{
			Panel->RemoveChild(Selectors[Target]);
			Selectors.Remove(Target);
		}
	}

	// Add new selectors
	for(const TScriptInterface<ITargetable>& Target : Targets)
	{
		if(IsValid(Player) && Target->IsTargetable(Player) && !Selectors.Contains(Target.GetObject()))
		{
			USelector* Selector = CreateWidget<USelector>(this, Target->GetSelectorClass());
			Selector->Init(Target);
			Panel->AddChildToCanvas(Selector);
			Selectors.Add(Target.GetObject(), Selector);
		}
	}

	// Manually update selectors as they do not tick by themselves when hidden
	for(const TPair<TObjectPtr<UObject>, TObjectPtr<USelector>>& Pair : Selectors)
	{
		Pair.Value->Update(MyGeometry);
	}
}

void USelectorCanvas::SetTargets(const TArray<TScriptInterface<ITargetable>>& InTargets)
{
	Targets = InTargets;
}

bool USelectorCanvas::ShouldRemove(const TScriptInterface<ITargetable>& Target)
{
	return !IsValid(Target.GetObject());
}
