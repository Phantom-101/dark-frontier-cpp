// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "StructureDetails.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureDetails : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> BackgroundButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UWidgetSwitcher> SelectorSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidget> NoSelector;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UStructurePartSelector> PartSelector;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UStructurePartSlotSelector> SlotSelector;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> InfoSwitcher;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UStructureInfo> StructureInfo;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UStructurePartInfo> PartInfo;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UStructurePartSlotInfo> SlotInfo;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UClickableCard> ApplyButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UClickableCard> ExitButton;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TArray<TSubclassOf<class AStructurePart>> AvailableParts;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TObjectPtr<class UStructurePartSlot> EditSlot;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TSubclassOf<AStructurePart> EditClass;

	virtual void NativeConstruct() override;

	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	
public:

	void Init();

	void Init(const TArray<TSubclassOf<AStructurePart>>& InClasses);

	void Select(class AStructure* InStructure);

	void Select(AStructurePart* InPart);

	void Select(UStructurePartSlot* InSlot);

	void Edit(UStructurePartSlot* InSlot);

	void Edit(TSubclassOf<AStructurePart> InClass);

	void Edit(const FText& InName);

protected:

	void OnBackgroundClicked() const;
	
};
