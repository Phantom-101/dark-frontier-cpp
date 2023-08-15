// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "CompatibleSectionSlotEntry.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UCompatibleSectionSlotEntry : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UStructureBuilder> StructureBuilder;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> NameText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> AddButton;
	
public:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:

	void OnAddButtonClicked() const;
	
};
