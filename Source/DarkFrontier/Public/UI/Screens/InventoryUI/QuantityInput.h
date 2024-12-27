// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "QuantityInput.generated.h"

class UCommonButtonBase;
class USlider;
class UCommonTextBlock;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UQuantityInput : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> QuantityText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<USlider> QuantitySlider;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> AddOneButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> AddTenButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> AddAllButton;
    	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> RemoveOneButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> RemoveTenButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> RemoveAllButton;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int MaxQuantity = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int CurrentQuantity = 0;

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

public:

	int GetMaxQuantity() const;

	void SetMaxQuantity(int InMax);

	int GetQuantity() const;

	void SetQuantity(int Target);

private:

	UFUNCTION()
	void HandleSlider(float Value);

	void HandleAddOne();

	void HandleAddTen();

	void HandleAddAll();

	void HandleRemoveOne();

	void HandleRemoveTen();

	void HandleRemoveAll();
	
};
