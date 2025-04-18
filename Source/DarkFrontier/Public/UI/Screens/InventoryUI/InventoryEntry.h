﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "InventoryEntry.generated.h"

class UCommonTextBlock;
class AStructure;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UInventoryEntry : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> NameText;

public:

	void Init(const AStructure* Structure) const;
	
};
