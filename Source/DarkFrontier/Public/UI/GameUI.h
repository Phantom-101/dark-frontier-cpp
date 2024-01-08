// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GameUI.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FActionsCollapseToggled, bool)

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UGameUI : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly)
	bool IsActionsCollapsed;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UImage> TurnBoundary;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> TurnCenter;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> TurnIndicator;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonListView> GameplayEffectList;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonListView> ActionGroupList;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> CollapseActionsButton;

public:

	FActionsCollapseToggled OnActionsCollapseToggled;

	bool GetIsActionsCollapsed() const;

protected:

	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

	virtual void NativeConstruct() override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateActions() const;

	void ToggleCollapseActions();
	
};
