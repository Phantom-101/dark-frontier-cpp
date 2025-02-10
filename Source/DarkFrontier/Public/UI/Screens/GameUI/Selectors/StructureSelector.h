// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructureSelector.generated.h"

class AStructure;
class UStructureIndicators;
class UCommonButtonBase;
class UWidgetSwitcher;
class UStructureIndication;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureSelector : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> SelectorButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UStructureIndicators> Indicators;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	TObjectPtr<AStructure> Target;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	bool TryInit(AStructure* InTarget);

	AStructure* GetTarget() const;

private:

	void HandleClick() const;

	void OnIndicationAdded(UStructureIndication* Indication) const;

	void OnIndicationRemoved(UStructureIndication* Indication) const;
	
};
