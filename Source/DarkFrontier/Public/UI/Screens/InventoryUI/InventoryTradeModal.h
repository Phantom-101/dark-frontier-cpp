// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "InventoryTradeModal.generated.h"

class UStructureInventory;
class UCommonTextBlock;
class UItem;
class UInventoryEntry;
class UCommonButtonBase;
class UQuantityInput;
class UListBox;
struct FItemStack;
class AStructure;

DECLARE_MULTICAST_DELEGATE_TwoParams(FInventoryTradeModalConfirmed, FItemStack, AStructure*)
DECLARE_MULTICAST_DELEGATE(FInventoryTradeModalCanceled)

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UInventoryTradeModal : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:

	FInventoryTradeModalConfirmed OnConfirmed;

	FInventoryTradeModalCanceled OnCanceled;

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListBox> TargetListBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UQuantityInput> QuantityInput;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> DeltaText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> ConfirmButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> CancelButton;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UInventoryEntry> InventoryEntryClass;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UStructureInventory> Inventory;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UItem> Item;

	virtual void NativeConstruct() override;

	virtual void NativeOnActivated() override;

	virtual void NativeOnDeactivated() override;

	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
	virtual bool NativeOnHandleBackAction() override;

public:

	void Init(UStructureInventory* InInventory, UItem* InItem, const TArray<AStructure*>& InTargets);

private:

	void HandleTargetChange(UObject* Target) const;

	void HandleQuantityChange(int Quantity) const;

	void HandleConfirm();

	void HandleCancel();
	
};
