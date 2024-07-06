// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/StructureSelectionLayer.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "Structures/Structure.h"
#include "UI/Screens/GameUI/StructureSelector.h"

void UStructureSelectionLayer::UpdateSelectors()
{
	TArray<AActor*> StructureActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStructure::StaticClass(), StructureActors);

	TArray<AStructure*> Existing;
	TArray<UWidget*> ToRemove;
	for(UWidget* Widget : Panel->GetAllChildren())
	{
		const UStructureSelector* Selector = Cast<UStructureSelector>(Widget);
		if(IsValid(Selector) && IsValid(Selector->Target))
		{
			Existing.Add(Selector->Target);
		}
		else
		{
			ToRemove.Add(Widget);
		}
	}

	for(UWidget* Widget : ToRemove)
	{
		Panel->RemoveChild(Widget);
	}

	for(AActor* StructureActor : StructureActors)
	{
		AStructure* Structure = Cast<AStructure>(StructureActor);
		if(!Existing.Contains(Structure))
		{
			UStructureSelector* Selector = CreateWidget<UStructureSelector>(this, SelectorClass);
			Selector->Target = Structure;
			Panel->AddChildToCanvas(Selector);
		}
	}
}
