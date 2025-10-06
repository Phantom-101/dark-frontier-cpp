// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "TargetInfo.generated.h"

class UTargetable;
class UInfoField;
class UCommonTextBlock;
/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UTargetInfo : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> TitleText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidget> ContentVisibility;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> ContentText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> DistanceField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> SpeedField;

public:

	void Init(const UTargetable* Target) const;

private:

	void SetContent(const FText& Content) const;
	
};
