// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Screens/Flight/Selectors/Selector.h"
#include "AsteroidSelector.generated.h"

class UArc;
class UItem;
class UMultiArc;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UAsteroidSelector : public USelector
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UMultiArc> CompositionArcs;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TArray<TObjectPtr<UItem>> Items;
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TArray<TObjectPtr<UArc>> Arcs;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	float MaxWeight = 0;

public:

	virtual void Init(const TScriptInterface<ITargetable>& InTarget) override;

protected:

	virtual void UpdateSelector(const FGeometry& CanvasGeometry) override;
	
};
