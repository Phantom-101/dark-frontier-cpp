// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Structures/StructureLayoutData.h"
#include "BuildScreen.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UBuildScreen : public UCommonActivatableWidget
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
	TObjectPtr<class UStructureSlotSelector> SlotSelector;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> InfoSwitcher;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UStructureInfo> StructureInfo;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UStructurePartInfo> PartInfo;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UStructureSlotInfo> SlotInfo;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> ExitButton;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class AStructure> StructureClass;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TArray<TSubclassOf<class AStructurePart>> AvailableParts;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TObjectPtr<AStructure> TargetStructure;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	FStructureLayoutData SavedLayout;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TObjectPtr<class UStructureSlot> BaseSlot;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TSubclassOf<AStructurePart> PartType;

	FDelegateHandle OnLayoutChangedHandle;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	
public:

	void ClearAvailableParts();

	void SetAvailableParts(const TArray<TSubclassOf<AStructurePart>>& InTypes);

	void InitStructure(class AStructure* InStructure);

	void SelectStructure();

	void SelectPart(AStructurePart* InPart);

	void SelectSlot(UStructureSlot* InSlot);

	void SetBaseSlot(UStructureSlot* InSlot);

	void SetPartType(const TSubclassOf<AStructurePart>& InClass);

	void AttachWithSlotName(const FText& InName);

protected:

	void OnBackgroundClicked() const;

	void OnLayoutChanged();
	
	void OnExitButtonClicked();
	
};
