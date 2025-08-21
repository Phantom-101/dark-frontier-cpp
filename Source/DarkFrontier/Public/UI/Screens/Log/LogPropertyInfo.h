// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "LogPropertyInfo.generated.h"

class AStructure;
class UInfoField;
class ULogPropertyEntry;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ULogPropertyInfo : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<ULogPropertyEntry> Header;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> PositionField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> OrderField;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> VolumeField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> MassField;

public:

	void Init(AStructure* Structure) const;
	
};
