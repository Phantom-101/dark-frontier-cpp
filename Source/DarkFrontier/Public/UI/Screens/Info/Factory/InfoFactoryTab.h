// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Screens/Info/InfoTab.h"
#include "InfoFactoryTab.generated.h"

class UListView;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UInfoFactoryTab : public UInfoTab
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListView> ListView;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
