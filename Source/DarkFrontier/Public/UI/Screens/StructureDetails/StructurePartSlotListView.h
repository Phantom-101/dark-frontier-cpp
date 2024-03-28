// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructurePartSlotListView.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructurePartSlotListView : public UCommonUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> NameText;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonListView> SlotList;

public:

	void Init(class AStructure* InTarget, const class UStructurePartSlotType* InType) const;
	
};
