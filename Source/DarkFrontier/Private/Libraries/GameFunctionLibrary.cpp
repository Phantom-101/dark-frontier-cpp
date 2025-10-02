// Fill out your copyright notice in the Description page of Project Settings.

#include "Libraries/GameFunctionLibrary.h"
#include "Structures/StructureController.h"

AStructureController* UGameFunctionLibrary::GetPlayerController(const UObject* WorldContext)
{
	return Cast<AStructureController>(WorldContext->GetWorld()->GetFirstPlayerController());
}

AStructure* UGameFunctionLibrary::GetPlayerStructure(const UObject* WorldContext)
{
	const AStructureController* Controller = GetPlayerController(WorldContext);
	return IsValid(Controller) ? Cast<AStructure>(Controller->GetPawn()) : nullptr;
}

AFaction* UGameFunctionLibrary::GetPlayerFaction(const UObject* WorldContext)
{
	const AStructure* Structure = GetPlayerStructure(WorldContext);
	return IsValid(Structure) ? Structure->GetAffiliation()->GetFaction() : nullptr;
}

ASector* UGameFunctionLibrary::GetPlayerSector(const UObject* WorldContext)
{
	const AStructure* Structure = GetPlayerStructure(WorldContext);
	return IsValid(Structure) ? Structure->GetSectorLocation()->GetSector() : nullptr;
}

bool UGameFunctionLibrary::IsPlayer(const AStructure* Structure)
{
	return Structure == GetPlayerStructure(Structure);
}

bool UGameFunctionLibrary::IsSelected(const UTargetable* Targetable)
{
	const AStructureController* PlayerController = GetPlayerController(Targetable);
	return IsValid(PlayerController) && PlayerController->GetSelectTarget() == Targetable;
}
