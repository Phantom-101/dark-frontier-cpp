// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructurePartSelector.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructurePartSelector : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonListView> OptionList;

public:

	void PopulateOptions(TArray<TSubclassOf<class AStructurePart>> InOptions, const class UStructureSlot* InSlot) const;
	
};
