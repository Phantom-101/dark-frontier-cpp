// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructureSlotInfo.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureSlotInfo : public UCommonUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> NameText;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UStructurePartCard> PartCard;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UStructureSlotCard> AttachedSlotCard;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<class UBuildScreen> Screen;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<class UStructureSlot> TargetSlot;

public:

	UStructureSlot* GetTarget() const;

	void SetTarget(UStructureSlot* InTargetSlot);
	
};
