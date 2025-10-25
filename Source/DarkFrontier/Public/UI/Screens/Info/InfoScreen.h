// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Screens/Screen.h"
#include "InfoScreen.generated.h"

class UInfoTab;
class UTab;
class UTabs;
class UCommonButtonBase;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UInfoScreen : public UScreen
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTabs> InfoTabs;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> CloseButton;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<TSubclassOf<UInfoTab>> TabClasses;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<AActor> Actor;

	virtual void NativeConstruct() override;

	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

public:

	AActor* GetActor() const;

	void SetActor(AActor* InActor);

private:

	void UpdateTabs();

	void HandleTabChanged(UCommonActivatableWidget* Widget);
	
};
