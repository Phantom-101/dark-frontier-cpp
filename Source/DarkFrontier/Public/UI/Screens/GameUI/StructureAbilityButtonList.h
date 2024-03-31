// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructureAbilityButtonList.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureAbilityButtonList : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonListView> PartList;

public:

	void UpdateButtons(class AStructure* InStructure) const;
	
};
