// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "FactionInfo.generated.h"

class ASector;
class AFaction;
class UInfoField;
class UFactionEntry;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UFactionInfo : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UFactionEntry> Header;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> TypeField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> HomeField;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> WealthField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> PowerField;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> ReputationField;

public:

	void Init(AFaction* Faction) const;

private:

	static FText GetHomeText(const ASector* Home);
	
	static FText GetWealthText(float Balance);

	static FText GetPowerText(float Power);

	static FText GetReputationText(float Reputation);
	
};
