// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/Targetable.h"
#include "Macros.h"
#include "Libraries/GameFunctionLibrary.h"
#include "Structures/StructureController.h"

bool ITargetable::IsSelectedByPlayer() const
{
	const AStructureController* PlayerController = UGameFunctionLibrary::GetPlayerController(Cast<UObject>(this));
	GUARD_RETURN(IsValid(PlayerController), false);
	return PlayerController->GetSelectTarget().GetObject() == Cast<UObject>(this);
}
