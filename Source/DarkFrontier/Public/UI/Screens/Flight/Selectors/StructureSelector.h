// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Selector.h"
#include "StructureSelector.generated.h"

class AStructure;
class UStructureIndicators;
class UCommonButtonBase;
class UWidgetSwitcher;
class UStructureIndication;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureSelector : public USelector
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UStructureIndicators> Indicators;

public:

	virtual void Init(const TScriptInterface<ITargetable>& InTarget) override;

private:

	void OnIndicationAdded(UStructureIndication* Indication) const;

	void OnIndicationRemoved(UStructureIndication* Indication) const;
	
};
