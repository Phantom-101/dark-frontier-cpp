// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructurePartInfo.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructurePartInfo : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> TypeText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UStructureCard> StructureCard;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UInfoField> HullField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> UpkeepField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonListView> SlotCardList;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<class UStructureDetails> Screen;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<class AStructurePart> TargetPart;

public:

	void SetTarget(AStructurePart* InTargetPart);
	
};
