// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructureSelector.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureSelector : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> SelectorButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UOverlay> IndicatorOverlay;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	TObjectPtr<class AStructure> Target;
	
protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	void OnClicked() const;
	
};
