// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructureIndicators.generated.h"

class UStructureIndication;
class UStructureIndicatorGroup;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UStructureIndicators : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCanvasPanel> IndicatorCanvas;

public:

	UFUNCTION(BlueprintCallable)
	void AddIndicator(UStructureIndication* Indication);

	UFUNCTION(BlueprintCallable)
	void RemoveIndicator(UStructureIndication* Indication);

protected:
	
	UFUNCTION(BlueprintCallable)
	UStructureIndicatorGroup* GetIndicatorGroup(UStructureIndication* Indication);

};
