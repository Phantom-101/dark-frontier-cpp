// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Flight/Selectors/AsteroidSelector.h"
#include "Environment/Asteroid.h"
#include "UI/Widgets/Visuals/Arc.h"
#include "UI/Widgets/Visuals/MultiArc.h"

void UAsteroidSelector::Init(const TScriptInterface<ITargetable>& InTarget)
{
	const AAsteroid* Asteroid = Cast<AAsteroid>(InTarget.GetObject());
	if(!ensureMsgf(IsValid(Asteroid), TEXT("Null or invalid target passed to asteroid selector")))
	{
		return;
	}

	Super::Init(InTarget);

	Arcs.Add(Asteroid->GetComposition(), CompositionArcs->AddArc());
}

void UAsteroidSelector::Tick(const FGeometry& CanvasGeometry)
{
	Super::Tick(CanvasGeometry);

	const AAsteroid* Asteroid = Cast<AAsteroid>(Target.GetObject());
	for(const TPair<TObjectPtr<UItem>, TObjectPtr<UArc>>& Pair : Arcs)
	{
		Pair.Value->SetLength(1 - Asteroid->GetDepletedAmount() / Asteroid->GetMaxAmount());
	}
}
