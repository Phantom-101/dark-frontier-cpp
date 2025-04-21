// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureLayoutConnection.h"
#include "StructureLayoutPart.h"
#include "StructureLayoutData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DARKFRONTIER_API FStructureLayoutData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, SaveGame)
	TArray<FStructureLayoutPart> Parts;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, SaveGame)
	TArray<FStructureLayoutConnection> Connections;

	FStructureLayoutData();

	FStructureLayoutData(const class AStructure* InStructure);
	
};
