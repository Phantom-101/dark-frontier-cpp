// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructurePartCardList.generated.h"

class AStructurePart;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructurePartCardList : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> HeaderText;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonListView> PartList;
	
public:

	void SetHeader(const FText& InHeader) const;

	void SetHeaderColor(const FLinearColor& InColor) const;

	void SetParts(const TArray<AStructurePart*>& InParts) const;
	
};
