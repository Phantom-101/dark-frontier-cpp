// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Flight/Selectors/ItemPodSelector.h"
#include "Macros.h"
#include "Items/ItemPod.h"

void UItemPodSelector::Update(const FGeometry& CanvasGeometry)
{
	Super::Update(CanvasGeometry);

	const AItemPod* ItemPod = Target->GetOwner<AItemPod>();
	GUARD(IsValid(ItemPod));

	Position(CanvasGeometry, ItemPod->GetActorLocation());
}
