// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructurePartControls.h"
#include "TractorBeamControls.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UTractorBeamControls : public UStructurePartControls
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> ToggleButton;
	
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	void Toggle() const;
	
};
