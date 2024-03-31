// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Structures/StructureLayout.h"
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
	TObjectPtr<UCommonButtonBase> ApplyButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> ExitButton;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class AStructure> StructureClass;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TArray<TSubclassOf<class AStructurePart>> AvailableParts;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TObjectPtr<AStructure> TargetStructure;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	FStructureLayout SavedLayout;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TObjectPtr<class UStructurePartSlot> EditSlot;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TSubclassOf<AStructurePart> EditClass;

	FDelegateHandle OnLayoutChangedHandle;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

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

	void OnLayoutChanged();

	void OnApplyButtonClicked();

	void OnExitButtonClicked();
	
};
