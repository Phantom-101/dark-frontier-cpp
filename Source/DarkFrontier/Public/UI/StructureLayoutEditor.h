// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructureLayoutEditor.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UStructureLayoutEditor : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonListView> Parts;
	
public:

	UFUNCTION(BlueprintCallable)
	void UpdateView(class AStructure* Target) const;
	
};
