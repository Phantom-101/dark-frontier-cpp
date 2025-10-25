// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Screens/Info/InfoTab.h"
#include "InfoLayoutTab.generated.h"

class UListView;
class UInfoField;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UInfoLayoutTab : public UInfoTab
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> EnergyField;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> UpkeepField;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListView> ListView;

public:

	virtual bool IsRelevant(AActor* Actor) const override;

protected:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
