// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "TabOption.generated.h"

class UTab;
class UCommonTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UTabOption : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> IconImage;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> NameText;

public:

	void Init(UTab* Tab) const;
	
};
