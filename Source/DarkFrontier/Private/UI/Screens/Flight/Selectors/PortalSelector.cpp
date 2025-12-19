// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Flight/Selectors/PortalSelector.h"
#include "Sectors/Portal.h"

void UPortalSelector::Update(const FGeometry& CanvasGeometry)
{
	Super::Update(CanvasGeometry);

	const APortal* Portal = Target->GetOwner<APortal>();
	GUARD(IsValid(Portal));

	Position(CanvasGeometry, Portal->GetActorLocation());
}
