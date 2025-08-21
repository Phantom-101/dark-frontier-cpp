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
	TMap<TObjectPtr<UItem>, TObjectPtr<UArc>> Arcs;

public:

	virtual void Init(const TScriptInterface<ITargetable>& InTarget) override;

protected:

	virtual void Tick(const FGeometry& CanvasGeometry) override;
	
};
