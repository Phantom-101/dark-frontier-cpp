// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructurePartInfo.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructurePartInfo : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> TypeText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UStructureCard> StructureCard;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UInfoField> HullField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> UpkeepField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> TypeModeButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> ListModeButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UWidgetSwitcher> SlotListSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UScrollBox> TypeList;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonListView> SlotCardList;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class UStructureSlotCardList> CardListClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class UCommonButtonStyle> SelectedStyle;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UCommonButtonStyle> UnSelectedStyle;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<class UStructureDetails> Screen;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<class AStructurePart> TargetPart;

	FDelegateHandle OnLayoutChangedHandle;
    
	virtual void NativeConstruct() override;

public:

	AStructurePart* GetTarget() const;

	void SetTarget(AStructurePart* InTargetPart);

private:
	
	void RebuildTypeMode();

	void RebuildListMode() const;

	void OnTypeModeSelected() const;

	void OnListModeSelected() const;

	void OnLayoutChanged();
	
};
