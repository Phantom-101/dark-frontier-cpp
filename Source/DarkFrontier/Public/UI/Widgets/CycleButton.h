// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "CycleButton.generated.h"

class UCommonTextBlock;
class UCommonButtonBase;

DECLARE_MULTICAST_DELEGATE_OneParam(FOptionSelected, int)

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UCycleButton : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> OptionText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> LeftButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> RightButton;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TArray<FText> Options;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	int SelectedIndex = 0;

	FOptionSelected OnOptionSelected;
	
	virtual void NativeConstruct() override;

public:

	void SetOptions(const TArray<FText>& InOptions);

	void SelectLeft();

	void SelectRight();

	void SetSelected(int Target);

private:
	
	int GetBounded(int Target) const;
	
};
