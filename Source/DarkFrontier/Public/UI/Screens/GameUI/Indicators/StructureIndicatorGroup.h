// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructureIndicatorGroup.generated.h"

class UStructureIndicator;
class UStructureIndication;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UStructureIndicatorGroup : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UPanelWidget> PanelWidget;

public:

	UFUNCTION(BlueprintCallable)
	UStructureIndicator* GetIndicator(UStructureIndication* Indication);

	UFUNCTION(BlueprintCallable)
	void AddIndicator(UStructureIndication* Indication, const TSubclassOf<UStructureIndicator>& IndicatorClass);

	UFUNCTION(BlueprintCallable)
	void RemoveIndicator(UStructureIndication* Indication);
	
};
