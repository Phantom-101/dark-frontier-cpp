// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureLayoutConnection.h"
#include "StructureLayoutPart.h"
#include "StructureLayout.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DARKFRONTIER_API FStructureLayout
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, SaveGame)
	bool IsEditorAuthoring = true;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, SaveGame)
	TArray<FStructureLayoutPart> Parts;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, SaveGame)
	TArray<FStructureLayoutConnection> Connections;

	FStructureLayout();

	FStructureLayout(const class AStructure* InStructure);
	
};
