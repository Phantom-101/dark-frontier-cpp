// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "SelectorCanvas.generated.h"

class UTargetable;
class USelector;

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
	TArray<TObjectPtr<UTargetable>> Targets;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TMap<TObjectPtr<UTargetable>, TObjectPtr<USelector>> Selectors;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	void SetTargets(const TArray<TObjectPtr<UTargetable>>& InTargets);

private:
	
	static bool ShouldRemove(const TObjectPtr<UTargetable>& Target);
	
};
