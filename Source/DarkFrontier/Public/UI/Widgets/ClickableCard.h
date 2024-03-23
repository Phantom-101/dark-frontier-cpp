// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "ClickableCard.generated.h"

DECLARE_DELEGATE(FCardClicked);

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UClickableCard : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	FCardClicked OnClicked;

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonBorder> Border;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> ClickArea;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class UCommonBorderStyle> Style;

	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;

private:

	void OnCardClicked() const;
	
};
