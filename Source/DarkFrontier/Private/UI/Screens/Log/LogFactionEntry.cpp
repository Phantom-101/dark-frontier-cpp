// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Log/LogFactionEntry.h"
#include "CommonTextBlock.h"
#include "Factions/Faction.h"
#include "Structures/Structure.h"
#include "UI/Widgets/Visuals/FillBar.h"

void ULogFactionEntry::Init(AFaction* InFaction)
{
	Faction = InFaction;

	NameText->SetText(Faction->GetFactionName());

	AFaction* PlayerFaction = Cast<AStructure>(GetWorld()->GetFirstPlayerController()->GetPawn())->GetOwningFaction();
	if(Faction == PlayerFaction)
	{
		RelationBar->SetForegroundStyle(PlayerStyle);
		
		RelationBar->SetPivot(GetStart(1));
		RelationBar->SetFill(GetFill(1));
	}
	else
	{
		const float Relation = Faction->GetRelation(PlayerFaction);

		RelationBar->SetForegroundStyle(Relation > 0 ? PositiveStyle : NegativeStyle);

		RelationBar->SetPivot(GetStart(Relation));
		RelationBar->SetFill(GetFill(Relation));
	}
}

void ULogFactionEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);
	Init(Cast<AFaction>(ListItemObject));
}

FVector2D ULogFactionEntry::GetStart(const float Relation)
{
	const float Fill = GetFill(Relation).X;
	const float Left = FMath::Min(Relation / 2 + 0.5, 0.5);
	return FVector2D(Left / (1 - Fill), 0);
}

FVector2D ULogFactionEntry::GetFill(const float Relation)
{
	return FVector2D(FMath::Abs(Relation) / 2, 1);
}
