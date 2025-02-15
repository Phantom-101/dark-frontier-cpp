// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/LogUI/FactionOption.h"
#include "CommonTextBlock.h"
#include "Factions/Faction.h"
#include "Structures/Structure.h"
#include "UI/Widgets/Visuals/FillBar.h"

void UFactionOption::Init(AFaction* InFaction)
{
	Faction = InFaction;

	NameText->SetText(Faction->GetFactionName());

	AFaction* PlayerFaction = Cast<AStructure>(GetWorld()->GetFirstPlayerController()->GetPawn())->GetOwningFaction();
	if(Faction == PlayerFaction)
	{
		RelationBar->SetStyle(PlayerStyle);
		
		RelationBar->SetStart(GetStart(1));
		RelationBar->SetFill(GetFill(1));
	}
	else
	{
		const float Relation = Faction->GetRelation(PlayerFaction);

		RelationBar->SetStyle(Relation > 0 ? PositiveStyle : NegativeStyle);

		RelationBar->SetStart(GetStart(Relation));
		RelationBar->SetFill(GetFill(Relation));
	}
}

FVector2D UFactionOption::GetStart(const float Relation)
{
	const float Fill = GetFill(Relation).X;
	const float Left = FMath::Min(Relation / 2 + 0.5, 0.5);
	return FVector2D(Left / (1 - Fill), 0);
}

FVector2D UFactionOption::GetFill(const float Relation)
{
	return FVector2D(FMath::Abs(Relation) / 2, 1);
}
