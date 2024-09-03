// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "StructureValidationResult.generated.h"

UENUM(BlueprintType)
enum class EStructureValidationResult : uint8
{
	Valid,
	SelfIntersecting,
	UpkeepExceeded,
	GroupLimitExceeded
};
