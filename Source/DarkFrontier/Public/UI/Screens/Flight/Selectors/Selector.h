// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Selector.generated.h"

class UTargetable;
class UCommonButtonBase;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API USelector : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> SelectButton;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	TObjectPtr<UTargetable> Target;

	virtual void NativeConstruct() override;

public:

	virtual void Init(UTargetable* InTarget);

	virtual void Update(const FGeometry& CanvasGeometry);

protected:

	void Position(const FGeometry& CanvasGeometry, const FVector& WorldPosition);

private:

	void Select() const;
	
};
