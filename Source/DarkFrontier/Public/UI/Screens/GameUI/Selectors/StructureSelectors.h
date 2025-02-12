// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructureSelectors.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureSelectors : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCanvasPanel> Panel;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<class UStructureSelector> SelectorClass;

public:

	UFUNCTION(BlueprintCallable)
	void UpdateSelectors();
	
};
