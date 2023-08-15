// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "SectionSlotLayoutEditor.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API USectionSlotLayoutEditor : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UStructureSectionSlot> SectionSlot;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UStructureBuilder> StructureBuilder;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FLinearColor HighlightColor;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonBorder> Highlight;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> NameText;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> TypeText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> IdText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> AddButton;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> RemoveButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> DisconnectButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> ViewButton;

public:
	
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

protected:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	
	void OnAddButtonClicked() const;

	void OnRemoveButtonClicked() const;

	void OnDisconnectButtonClicked() const;

	void OnViewButtonClicked() const;
	
};
