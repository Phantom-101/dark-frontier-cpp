// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "StructureAbilityButton.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureAbilityButton : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> AbilityButton;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UImage> RadialProgressBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> AbilityIcon;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UMaterialInterface> Material;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UMaterialInstance> MaterialInstance;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<class UStructurePartAbilityClass> AbilityClassObj;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:

	void OnAbilityButtonClicked() const;
	
};
