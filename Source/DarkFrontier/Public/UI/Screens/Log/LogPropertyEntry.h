// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/Interaction/SelectableEntry.h"
#include "LogPropertyEntry.generated.h"

class AStructure;
class UFillBar;
class UCommonTextBlock;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ULogPropertyEntry : public USelectableEntry
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

public:

	void Init(AStructure* InStructure);

protected:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
