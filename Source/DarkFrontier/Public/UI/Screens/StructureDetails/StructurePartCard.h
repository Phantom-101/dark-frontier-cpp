// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "StructurePartCard.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructurePartCard : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> CardButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> TypeText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> RemoveButton;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> LookButton;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<class AStructurePart> TargetPart;

	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

public:

	void SetTarget(AStructurePart* InTargetPart);

private:

	void OnCardClicked() const;
	
};
