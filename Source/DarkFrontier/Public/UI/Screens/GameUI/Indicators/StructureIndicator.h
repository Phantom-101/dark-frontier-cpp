// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructureIndicator.generated.h"

class UStructureIndicatorGroup;
class UStructureIndication;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UStructureIndicator : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UStructureIndicatorGroup> GroupClass;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UStructureIndication> Indication;

public:

	TSubclassOf<UStructureIndicatorGroup> GetGroupClass() const;

	bool TryInit(UStructureIndication* InIndication);

	UStructureIndication* GetIndication() const;
	
};
