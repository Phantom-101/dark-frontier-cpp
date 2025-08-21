// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Screens/Screen.h"
#include "InventoryTransferModal.generated.h"

class UListView;
class AStructure;
class UItem;
class UInventory;
class UCommonButtonBase;
class UQuantityInput;
struct FItemStack;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UInventoryTransferModal : public UScreen
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListView> ListView;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UQuantityInput> QuantityInput;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> ConfirmButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> CancelButton;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UInventory> Inventory;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UItem> Item;

	virtual void NativeConstruct() override;

public:

	void Init(UInventory* InInventory, UItem* InItem, const TArray<AStructure*>& InTargets);

private:

	void HandleTargetChange(UObject* Target) const;

	void HandleConfirm();

	void HandleCancel();
	
};
