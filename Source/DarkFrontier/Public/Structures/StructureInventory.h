// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Inventory.h"
#include "StructureInventory.generated.h"

class AStructure;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureInventory : public UInventory
{
	GENERATED_BODY()

public:

	static UStructureInventory* CreateInventory(AStructure* Structure);

	UFUNCTION(BlueprintCallable)
	AStructure* GetStructure() const;
	
};
