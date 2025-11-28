// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Screens/Screen.h"
#include "StationScreen.generated.h"

class UInfoScreen;class URepairScreen;
class URefitScreen;
class UTradeScreen;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UStationScreen : public UScreen
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonBoundActionButton> ShipButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonBoundActionButton> TradeButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonBoundActionButton> RepairButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonBoundActionButton> RefitButton;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonBoundActionButton> PassengersButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonBoundActionButton> UndockButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonBoundActionButton> StationButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonBoundActionButton> HangarButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonBoundActionButton> BuyShipButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonBoundActionButton> TravelButton;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonBoundActionButton> MissionsButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonBoundActionButton> ExitShipButton;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UInputAction> ShipAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UInputAction> TradeAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UInputAction> RepairAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UInputAction> RefitAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UInputAction> UndockAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UInputAction> StationAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UInfoScreen> InfoScreenClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UTradeScreen> TradeScreenClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<URepairScreen> RepairScreenClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<URefitScreen> RefitScreenClass;

	virtual void RegisterBindings() override;

	virtual UWidget* NativeGetDesiredFocusTarget() const override;

	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

private:

	void ShipInfo();

	void UndockPlayer();

	void StationInfo();
	
};
