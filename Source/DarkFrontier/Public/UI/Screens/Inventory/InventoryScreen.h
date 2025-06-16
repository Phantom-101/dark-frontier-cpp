// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "InventoryScreen.generated.h"

class UStructureInventory;
class UItemStackEntry;
class UListBox;
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
class UCommonButtonBase;
class UItem;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UInventoryScreen : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:

	// TODO add close button

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> SwitchButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListBox> ItemListBox;

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
	TSubclassOf<UItemStackEntry> ItemStackEntryClass;

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
	TObjectPtr<AStructure> Structure;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UCommonActivatableWidget> CurrentModal;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

public:

	void SetStructure(AStructure* InStructure);

	AStructure* GetStructure() const;

	UStructureInventory* GetInventory() const;

private:

	void Rebuild();

	void HandleSwitch();

	void HandleSwitchConfirmed(UObject* Selection);

	void HandleTrade();

	void HandleTransfer();

	void HandleDispose();

};
