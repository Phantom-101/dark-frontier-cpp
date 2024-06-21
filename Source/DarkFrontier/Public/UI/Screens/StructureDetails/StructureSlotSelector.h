// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructureSlotSelector.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureSlotSelector : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonListView> OptionList;

public:

	void PopulateOptions(TSubclassOf<class AStructurePart> InClass, const class UStructureSlot* InSlot) const;
	
};
