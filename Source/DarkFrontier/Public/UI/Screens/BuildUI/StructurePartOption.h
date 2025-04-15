// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "StructurePartOption.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructurePartOption : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> CardButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> TypeText;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TSubclassOf<class AStructurePart> PartClass;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:

	void OnOptionClicked() const;
	
};
