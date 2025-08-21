// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/Interaction/SelectableEntry.h"
#include "TradeEntry.generated.h"

class UStructureInventory;
class AStructure;
class UItem;
class UCommonButtonBase;
class UCommonTextBlock;
class UImage;

UCLASS()
class UTradeEntryObject : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UItem> Item;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UStructureInventory> Inventory;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UStructureInventory> Other;

	static UTradeEntryObject* New(UItem* Item, UStructureInventory* Inventory, UStructureInventory* Other);
	
};

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UTradeEntry : public USelectableEntry
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> IconImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> NameText;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> ShipText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> StationText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> BuyText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> SellText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> BuyButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> SellButton;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UItem> Item;
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UStructureInventory> Inventory;
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UStructureInventory> Other;

	virtual void NativeConstruct() override;

public:

	void Init(UItem* InItem, UStructureInventory* InInventory, UStructureInventory* InOther);

protected:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	void HandleBuy();

	void HandleSell();
	
};
