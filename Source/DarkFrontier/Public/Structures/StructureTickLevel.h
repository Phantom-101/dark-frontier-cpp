// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "StructureTickLevel.generated.h"

UENUM(BlueprintType)
enum class EStructureTickLevel : uint8
{
    Invalid,
    Full,
    Limited,
    None
};
