// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "StructurePartActionGroupEntry.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructurePartActionGroupEntry : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UStructurePartActionGroup> ActionGroup;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> GroupButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonListView> ActionList;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:

	void OnGroupButtonClicked() const;

	void OnCollapseToggled(bool Target) const;
	
};
