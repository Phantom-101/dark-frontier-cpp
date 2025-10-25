// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "InfoTab.generated.h"

class UTab;
class UInfoScreen;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UInfoTab : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UTexture2D> TabIcon;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText TabName;
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UInfoScreen> Screen;

public:

	virtual bool IsRelevant(AActor* Actor) const;

	const TObjectPtr<UTexture2D>& GetTabIcon() const;

	const FText& GetTabName() const;

	static UTab* NewTab(const TSubclassOf<UInfoTab>& TabClass);

	virtual void Init(UInfoScreen* InScreen);
	
};
