// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "StructureSlotOption.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureSlotOption : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> CardButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> NameText;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	FText SlotName;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:

	void OnOptionClicked() const;
	
};
