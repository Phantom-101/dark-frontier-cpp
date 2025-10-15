// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "UI/Screens/Info/InfoTab.h"
#include "InfoOverviewTab.generated.h"

class UInfoScreen;
class UStructureOverview;
class UWidgetSwitcher;
class UCommonTextBlock;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UInfoOverviewTab : public UInfoTab
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> NameText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> OverviewSwitcher;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidget> UnknownOverview;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UStructureOverview> StructureOverview;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
