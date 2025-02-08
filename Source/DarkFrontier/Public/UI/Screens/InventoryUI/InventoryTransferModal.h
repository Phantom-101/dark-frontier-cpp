// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "InventoryTransferModal.generated.h"

class AStructure;
class UInventoryOption;
class UListBox;
class UItem;
class UInventory;
class UCommonButtonBase;
class UQuantityInput;
struct FItemStack;

DECLARE_MULTICAST_DELEGATE_TwoParams(FInventoryTransferModalConfirmed, FItemStack, AStructure*)
DECLARE_MULTICAST_DELEGATE(FInventoryTransferModalCanceled)

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UInventoryTransferModal : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	FInventoryTransferModalConfirmed OnConfirmed;

	FInventoryTransferModalCanceled OnCanceled;

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListBox> TargetListBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UQuantityInput> QuantityInput;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> ConfirmButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> CancelButton;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UInventoryOption> InventoryOptionClass;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UInventory> Inventory;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UItem> Item;

	virtual void NativeConstruct() override;

	virtual void NativeOnActivated() override;

	virtual void NativeOnDeactivated() override;

	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
	virtual bool NativeOnHandleBackAction() override;

public:

	void Init(UInventory* InInventory, UItem* InItem, const TArray<AStructure*>& InTargets);

private:

	void HandleTargetChange(UObject* Target) const;

	void HandleConfirm();

	void HandleCancel();
	
};
