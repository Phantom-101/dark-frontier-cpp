// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "MultiArc.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UMultiArc : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UOverlay> ArcOverlay;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class UArc> ArcClass;

public:

	void ClearArcs() const;

	UArc* AddArc();

	void RemoveArc(UArc* InArc) const;

	void RemoveArcAt(int32 Index) const;
	
};
