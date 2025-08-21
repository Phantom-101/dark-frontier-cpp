// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/Interaction/SelectableEntry.h"
#include "LogMailEntry.generated.h"

class UMail;
class UCommonTextBlock;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ULogMailEntry : public USelectableEntry
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> SubjectText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> TimeText;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UMail> Mail;

public:

	void Init(UMail* InMail);

protected:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
};
