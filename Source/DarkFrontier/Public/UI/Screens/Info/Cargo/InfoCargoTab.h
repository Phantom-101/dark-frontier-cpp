// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Screens/Info/InfoTab.h"
#include "InfoCargoTab.generated.h"

class UInventory;
class UFillBar;
class UListView;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UInfoCargoTab : public UInfoTab
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UFillBar> VolumeBar;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UFillBar> MassBar;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListView> ListView;

public:

	virtual bool IsRelevant(AActor* Actor) const override;

protected:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	bool NeedsUpdate(const UInventory* Inventory) const;
	
};
