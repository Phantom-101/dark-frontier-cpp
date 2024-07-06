// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructureIndicator.generated.h"

class UStructureIndication;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UStructureIndicator : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	virtual UStructureIndication* GetIndication() const;
	
};
