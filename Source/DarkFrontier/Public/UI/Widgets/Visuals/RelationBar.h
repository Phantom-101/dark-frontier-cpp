// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FillBar.h"
#include "RelationBar.generated.h"

class AFaction;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API URelationBar : public UFillBar
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UCommonBorderStyle> PlayerStyle;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UCommonBorderStyle> PositiveStyle;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UCommonBorderStyle> NegativeStyle;

public:

	void Init(AFaction* InFaction);

	void Init(const AFaction* InReference, AFaction* InOther);

private:

	void SetBar(float Relation);
	
};
