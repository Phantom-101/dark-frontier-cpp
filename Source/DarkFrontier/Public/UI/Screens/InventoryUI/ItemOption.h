// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "ItemOption.generated.h"

class UCommonTextBlock;
class UItemObject;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UItemOption : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> NameText;

public:

	void Init(const UItemObject* ItemObject) const;
	
};
