// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "InventoryUI.generated.h"

class UItem;
class UInventory;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UInventoryUI : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UItemList> ItemList;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UWidgetSwitcher> InfoSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidget> NoItem;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidget> ItemInfo;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UImage> IconImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> NameText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> DescriptionText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UInfoField> QuantityField;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UInfoField> ValueField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UInfoField> VolumeField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UInfoField> MassField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> TradeButton;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> TransferButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> DisposeButton;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

public:

	UInventory* GetInventory() const;

	void SetInventory(UInventory* InInventory) const;
	
};
