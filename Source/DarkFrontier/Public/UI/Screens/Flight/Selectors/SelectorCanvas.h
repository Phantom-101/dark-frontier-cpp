// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "SelectorCanvas.generated.h"

class USelector;
class ITargetable;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API USelectorCanvas : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCanvasPanel> Panel;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TArray<TScriptInterface<ITargetable>> Targets;

	// Use object keys as map is not compatible with script interface keys
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TMap<TObjectPtr<UObject>, TObjectPtr<USelector>> Selectors;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	UFUNCTION(BlueprintCallable)
	void SetTargets(const TArray<TScriptInterface<ITargetable>>& InTargets);

private:
	
	static bool ShouldRemove(const TScriptInterface<ITargetable>& Target);
	
};
