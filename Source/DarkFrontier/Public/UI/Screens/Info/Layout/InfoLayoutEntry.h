// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/Interaction/SelectableEntry.h"
#include "InfoLayoutEntry.generated.h"

class AStructurePart;
class UFillBar;
class UCommonTextBlock;
/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UInfoLayoutEntry : public USelectableEntry
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> NameText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UFillBar> ConditionBar;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<AStructurePart> Part;

public:

	void Init(AStructurePart* InPart);

protected:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
