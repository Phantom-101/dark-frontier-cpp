// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GameUI.generated.h"

class UStructurePartControlsMapping;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UGameUI : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UArc> HullArc;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UArc> ShieldArc;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UArc> EnergyArc;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UArc> SpeedArc;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UImage> TurnBoundary;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> TurnCenter;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> TurnIndicator;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonListView> GameplayEffectList;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UStructureSelectors> Selectors;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UScrollBox> PartControls;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> DockButton;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UStructurePartControlsMapping> ControlsMapping;

	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

	virtual void NativeConstruct() override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	void HandleDock() const;
	
};
