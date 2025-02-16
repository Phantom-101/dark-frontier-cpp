// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "FactionEntry.generated.h"

class UCommonBorderStyle;
class AFaction;
class UFillBar;
class UCommonTextBlock;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UFactionEntry : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> NameText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UFillBar> RelationBar;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UCommonBorderStyle> PlayerStyle;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UCommonBorderStyle> PositiveStyle;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UCommonBorderStyle> NegativeStyle;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<AFaction> Faction;

public:

	void Init(AFaction* InFaction);

private:
	
	static FVector2D GetStart(float Relation);

	static FVector2D GetFill(float Relation);
	
};
