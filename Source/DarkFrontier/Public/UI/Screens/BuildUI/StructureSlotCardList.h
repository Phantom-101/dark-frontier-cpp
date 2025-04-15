// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructureSlotCardList.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureSlotCardList : public UCommonUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> NameText;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonListView> SlotList;

public:

	void Init(TArray<class UStructureSlot*> InSlots, const FText& InHeader, FLinearColor InColor) const;
	
};
