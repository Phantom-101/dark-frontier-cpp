// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureLayoutConnection.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DARKFRONTIER_API FStructureLayoutConnection
{
	GENERATED_BODY()

	/** Id of the part which is used as the reference position when physically attaching. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame)	
	FString PartAId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame)	
	FText PartASlot;

	/** Id of the part which is moved with regards to the reference when physically attaching. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame)
	FString PartBId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame)	
	FText PartBSlot;
	
	FStructureLayoutConnection();

	FStructureLayoutConnection(const class UStructurePartSlot* SlotA, const UStructurePartSlot* SlotB);

	bool IsValid() const;
	
};
