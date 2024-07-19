// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructurePartControl.h"
#include "PulseTurretControl.generated.h"

class APulseTurret;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UPulseTurretControl : public UStructurePartControl
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> ActivateButton;

public:

	TObjectPtr<APulseTurret> Turret;

protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	virtual AStructurePart* GetPart() override;

private:

	void OnClicked();
	
};
