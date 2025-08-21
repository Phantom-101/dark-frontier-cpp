// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructurePartFilter.h"
#include "Algo/AllOf.h"
#include "Algo/AnyOf.h"
#include "Structures/StructurePart.h"

bool FStructurePartFilter::Matches(const AStructurePart* Other) const
{
	return true;
}

bool FStructurePartFilter_MatchesAll::Matches(const AStructurePart* Other) const
{
	return Algo::AllOf(Filters, [=](const TInstancedStruct<FStructurePartFilter>& Filter)
	{
		return Filter.GetPtr<FStructurePartFilter>()->Matches(Other);
	});
}

bool FStructurePartFilter_MatchesAny::Matches(const AStructurePart* Other) const
{
	return Algo::AnyOf(Filters, [=](const TInstancedStruct<FStructurePartFilter>& Filter)
	{
		return Filter.GetPtr<FStructurePartFilter>()->Matches(Other);
	});
}

bool FStructurePartFilter_HasAll::Matches(const AStructurePart* Other) const
{
	FGameplayTagContainer PartTags;
	Other->GetOwnedGameplayTags(PartTags);
	return PartTags.HasAll(AllTags);
}

bool FStructurePartFilter_HasAny::Matches(const AStructurePart* Other) const
{
	FGameplayTagContainer PartTags;
	Other->GetOwnedGameplayTags(PartTags);
	return PartTags.HasAny(AnyTags);
}

bool FStructurePartFilter_HasNone::Matches(const AStructurePart* Other) const
{
	FGameplayTagContainer PartTags;
	Other->GetOwnedGameplayTags(PartTags);
	return !PartTags.HasAny(NoneTags);
}
