// Fill out your copyright notice in the Description page of Project Settings.

#include "Libraries/GameFunctionLibrary.h"
#include "Macros.h"
#include "Structures/StructureController.h"

AStructureController* UGameFunctionLibrary::GetPlayerController(const UObject* WorldContext)
{
	return Cast<AStructureController>(WorldContext->GetWorld()->GetFirstPlayerController());
}

AStructure* UGameFunctionLibrary::GetPlayerStructure(const UObject* WorldContext)
{
	const AStructureController* Controller = GetPlayerController(WorldContext);
	GUARD_RETURN(IsValid(Controller), nullptr);
	return Cast<AStructure>(Controller->GetPawn());
}

bool UGameFunctionLibrary::IsSelected(const TScriptInterface<ITargetable>& Targetable)
{
	const AStructureController* PlayerController = GetPlayerController(Targetable.GetObject());
	GUARD_RETURN(IsValid(PlayerController), false);
	return PlayerController->GetSelectTarget() == Targetable;
}
