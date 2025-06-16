// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructureIndicators.generated.h"

class UStructureIndicatorMapping;
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

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UStructureIndicatorMapping> Mapping;

public:

	UFUNCTION(BlueprintCallable)
	void AddIndicator(UStructureIndication* Indication) const;

	UFUNCTION(BlueprintCallable)
	void RemoveIndicator(UStructureIndication* Indication) const;

protected:
	
	UFUNCTION(BlueprintCallable)
	UStructureIndicatorGroup* GetGroup(TSubclassOf<UStructureIndicatorGroup> GroupClass) const;

};
