// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Screens/GameUI/StructureIndicator.h"
#include "ProgressIndicator.generated.h"

class UProgressIndication;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UProgressIndicator : public UStructureIndicator
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	TObjectPtr<UProgressIndication> Indication;

	virtual UStructureIndication* GetIndication() const override;
	
};
