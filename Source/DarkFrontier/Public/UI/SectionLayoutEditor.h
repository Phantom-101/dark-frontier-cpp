// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "SectionLayoutEditor.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API USectionLayoutEditor : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> TypeText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> IdText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> RootSectionText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonListView> SectionSlotList;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonListView> EquipmentSlotList;
	
public:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
};
