// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "InventoryUI.generated.h"

class UInventoryTradeModal;
class UInventoryTransferModal;
struct FItemStack;
class UInventoryDisposeModal;
class UInventoryEntry;
class AStructure;
class UListBoxModal;
class UInfoField;
class UCommonTextBlock;
class UImage;
class UWidgetSwitcher;
class UItemList;
class UCommonButtonBase;
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
	TObjectPtr<UCommonButtonBase> SwitchButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UItemList> ItemList;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> InfoSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidget> NoItem;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidget> ItemInfo;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> IconImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> NameText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> DescriptionText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> QuantityField;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> VolumeField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> MassField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> TradeButton;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> TransferButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> DisposeButton;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UListBoxModal> ListBoxModalClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UInventoryEntry> InventoryEntryClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UInventoryTradeModal> TradeModalClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UInventoryTransferModal> TransferModalClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UInventoryDisposeModal> DisposeModalClass;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<AStructure> CurrentStructure;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UCommonActivatableWidget> CurrentModal;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

public:

	void SetCurrentStructure(AStructure* InStructure);

	AStructure* GetCurrentStructure() const;

	UInventory* GetCurrentInventory() const;

private:

	void HandleSwitch();

	void HandleSwitchConfirmed(UObject* Selection);

	void HandleTrade();

	void HandleTradeConfirmed(const FItemStack Trade, AStructure* Target) const;

	void HandleTransfer();

	void HandleTransferConfirmed(const FItemStack Transfer, AStructure* Target) const;

	void HandleDispose();

	void HandleDisposeConfirmed(const FItemStack Dispose) const;
	
};
