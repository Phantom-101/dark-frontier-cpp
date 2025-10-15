// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Flight/TargetInfo.h"
#include "CommonTextBlock.h"
#include "Macros.h"
#include "Factions/Affiliation.h"
#include "Factions/Faction.h"
#include "Libraries/GameFunctionLibrary.h"
#include "Structures/Structure.h"
#include "Structures/Targetable.h"
#include "UI/Widgets/Visuals/InfoField.h"

void UTargetInfo::Init(const UTargetable* Target) const
{
	GUARD(IsValid(Target));

	AActor* Actor = Target->GetOwner();

	FText Title = FText::FromString(Actor->GetActorNameOrLabel());
	const UAffiliation* Affiliation = ACCESS_COMPONENT(Actor, Affiliation);
	if(IsValid(Affiliation) && IsValid(Affiliation->GetFaction()))
	{
		const FText& FactionName = Affiliation->GetFaction()->GetFactionName();
		Title = FText::FromString(FString::Printf(TEXT("%s (%s)"), *Title.ToString(), *FactionName.ToString()));
	}
	TitleText->SetText(Title);

	// TODO description for structure AI role
	SetContent(FText::GetEmpty());

	const AStructure* Player = UGameFunctionLibrary::GetPlayerStructure(this);
	if(IsValid(Player))
	{
		DistanceField->SetContentFromFloat((Actor->GetActorLocation() - Player->GetActorLocation()).Length() / 100);
	}
	else
	{
		DistanceField->SetContentFromString("-");
	}
	SpeedField->SetContentFromFloat(Actor->GetVelocity().Length() / 100);
}

void UTargetInfo::SetContent(const FText& Content) const
{
	ContentText->SetText(Content);
	ContentVisibility->SetVisibility(Content.IsEmptyOrWhitespace() ? ESlateVisibility::Collapsed : ESlateVisibility::SelfHitTestInvisible);
}
