// Fill out your copyright notice in the Description page of Project Settings.

#include "Sectors/SectorRoot.h"
#include "Macros.h"
#include "Sectors/Sector.h"
#include "Sectors/SectorLocation.h"

void USectorRoot::OnChildAttached(USceneComponent* ChildComponent)
{
	Super::OnChildAttached(ChildComponent);

	// If the owning actor is attached to another actor in the editor
	// USceneComponent::OnRegister will call USceneComponent::AttachToComponent with the pre-existing attach parent
	// Then UPrimitiveComponent::BeginPlay will detach automatically if it is a physics body

	// We automatically set the sector of any actors that were attached in the world outliner
	// This removes the need to manually set the sector reference for each SectorLocation
	// It does not matter if the component is a physics body and automatically detaches later

	GUARD(GetWorld()->IsGameWorld());

	ASector* Sector = GetOwner<ASector>();
	GUARD(IsValid(Sector));

	USectorLocation* Location = ACCESS_COMPONENT(ChildComponent->GetOwner(), SectorLocation);
	if(IsValid(Location))
	{
		Location->SetSector(Sector);
	}
}
