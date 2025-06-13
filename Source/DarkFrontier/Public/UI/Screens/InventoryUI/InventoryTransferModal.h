// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "InventoryTransferModal.generated.h"

class AStructure;
class UInventoryEntry;
class UListBox;
class UItem;
class UInventory;
class UCommonButtonBase;
class UQuantityInput;
struct FItemStack;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UInventoryTransferModal : public UCommonActivatableWidget
{
	GENERATED_BODY()

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
	TSubclassOf<UInventoryEntry> InventoryEntryClass;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UInventory> Inventory;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UItem> Item;

	virtual void NativeConstruct() override;

	virtual void NativeOnActivated() override;

	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
	virtual bool NativeOnHandleBackAction() override;

public:

	void Init(UInventory* InInventory, UItem* InItem, const TArray<AStructure*>& InTargets);

private:

	void HandleTargetChange(UObject* Target) const;

	void HandleConfirm();

	void HandleCancel();
	
};
