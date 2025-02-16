// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructureEntry.generated.h"

class AStructure;
class UFillBar;
class UCommonTextBlock;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UStructureEntry : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> NameText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UFillBar> ShieldBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
    TObjectPtr<UFillBar> HullBar;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<AStructure> Structure;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	void Init(AStructure* InStructure);
	
};
