// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Screens/Screen.h"
#include "RepairScreen.generated.h"

class UCommonTextBlock;
class UFillBar;
class UStripe;
class AStructure;
class AStructurePart;
class UListView;
class UCommonButtonBase;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API URepairScreen : public UScreen
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonBoundActionButton> CloseButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> ShieldButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UStripe> ShieldStripe;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UFillBar> ShieldBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> ShieldConditionText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> ShieldCostText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> HullButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UStripe> HullStripe;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UFillBar> HullBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> HullConditionText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> HullCostText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListView> ListView;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonBoundActionButton> SelectAllButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonBoundActionButton> DeselectAllButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> CostText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonBoundActionButton> ConfirmButton;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UInputAction> CloseAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UInputAction> SelectAllAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UInputAction> DeselectAllAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UInputAction> ConfirmAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool RepairShield = true;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool RepairHull = true;

	virtual void NativeConstruct() override;

	virtual void NativeOnActivated() override;

	virtual void RegisterBindings() override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	void UpdateStripes() const;

	void ToggleShield();

	void ToggleHull();

	void SelectAll();

	void DeselectAll();

	float GetTotalCost() const;

	void Confirm();
	
};
