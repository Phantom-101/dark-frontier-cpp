// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Screens/Screen.h"
#include "InventoryTradeModal.generated.h"

class UListView;
class UStructureInventory;
class UCommonTextBlock;
class UItem;
class UCommonButtonBase;
class UQuantityInput;
struct FItemStack;
class AStructure;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UInventoryTradeModal : public UScreen
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListView> ListView;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UQuantityInput> QuantityInput;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> DeltaText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> ConfirmButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> CancelButton;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UStructureInventory> Inventory;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UItem> Item;

	virtual void NativeConstruct() override;

public:

	void Init(UStructureInventory* InInventory, UItem* InItem, const TArray<AStructure*>& InTargets);

private:

	void HandleTargetChange(UObject* Target) const;

	void HandleQuantityChange(int Quantity) const;

	void HandleConfirm();

	void HandleCancel();
	
};
