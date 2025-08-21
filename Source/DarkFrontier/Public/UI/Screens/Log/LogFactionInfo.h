// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "LogFactionInfo.generated.h"

class UListView;
class URelationBar;
class UCommonTextBlock;
class ASector;
class AFaction;
class UInfoField;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ULogFactionInfo : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> NameText;

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

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<URelationBar> RelationBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListView> AlliesList;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListView> EnemiesList;

public:

	void Init(AFaction* Faction) const;

private:

	static FText GetHomeText(const ASector* Home);
	
	static FText GetWealthText(float Balance);

	static FText GetPowerText(float Power);

	static FText GetReputationText(float Reputation);
	
};
