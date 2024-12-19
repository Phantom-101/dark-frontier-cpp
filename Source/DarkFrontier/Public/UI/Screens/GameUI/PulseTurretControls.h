// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructurePartControls.h"
#include "PulseTurretControls.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UPulseTurretControls : public UStructurePartControls
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> ActivateButton;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual bool TryInitialize(AStructurePart* InPart) override;

private:

	void OnClicked();
	
};
