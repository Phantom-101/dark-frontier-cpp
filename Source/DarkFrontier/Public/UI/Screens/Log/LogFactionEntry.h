// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/Interaction/SelectableEntry.h"
#include "LogFactionEntry.generated.h"

class URelationBar;
class UCommonBorderStyle;
class AFaction;
class UCommonTextBlock;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ULogFactionEntry : public USelectableEntry
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> NameText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<URelationBar> RelationBar;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<AFaction> Faction;

public:

	void Init(AFaction* InFaction);

protected:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
	
	static FVector2D GetStart(float Relation);

	static FVector2D GetFill(float Relation);
	
};
