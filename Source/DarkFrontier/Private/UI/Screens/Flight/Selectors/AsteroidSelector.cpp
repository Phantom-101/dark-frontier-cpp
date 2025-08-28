// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Flight/Selectors/AsteroidSelector.h"
#include "CommonButtonBase.h"
#include "Macros.h"
#include "Environment/Asteroid.h"
#include "Libraries/GameFunctionLibrary.h"
#include "Libraries/ItemFunctionLibrary.h"
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

	TArray<TTuple<TObjectPtr<UItem>, float>> Pairs = Asteroid->GetComposition().Array();
	Algo::StableSortBy(Pairs, [](const TTuple<TObjectPtr<UItem>, float>& Pair) { return -Pair.Value; });
	for(const TTuple<TObjectPtr<UItem>, float> Pair : Pairs)
	{
		UArc* Arc = CompositionArcs->AddArc();
		Arc->SetColor(UItemFunctionLibrary::GetColor(Pair.Key).Get(FLinearColor::White));
		Items.Add(Pair.Key);
		Arcs.Add(Arc);
	}
	MaxWeight = Asteroid->GetMaxWeight();
}

void UAsteroidSelector::Update(const FGeometry& CanvasGeometry)
{
	Super::Update(CanvasGeometry);
	
	const AAsteroid* Asteroid = Cast<AAsteroid>(Target.GetObject());
	GUARD(IsValid(Asteroid));

	Position(CanvasGeometry, Asteroid->GetActorLocation());
	if(UGameFunctionLibrary::IsSelected(Target))
	{
		SelectButton->SetVisibility(ESlateVisibility::Collapsed);
		CompositionArcs->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		const float Multiplier = 1 - Asteroid->GetDepletedAmount() / Asteroid->GetMaxAmount();
		float Start = 0;
		for(int Index = 0; Index < Items.Num(); Index++)
		{
			const float Length = Asteroid->GetComposition()[Items[Index]] / MaxWeight * Multiplier;
			Arcs[Index]->SetStartAndLength(Start, Length);
			Start += Length;
		}
	}
	else
	{
		SelectButton->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		CompositionArcs->SetVisibility(ESlateVisibility::Collapsed);
	}
}
