// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "CommonUserWidget.h"
#include "StructureBuilder.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UStructureBuilder : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UConfirmationModal> ConfirmationModalClass;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AStructure> TargetStructure;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UStructureSectionSlot> SelectedSectionSlot;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UStructureEquipmentSlot> SelectedEquipmentSlot;

	UPROPERTY(BlueprintReadOnly)
	TArray<TSubclassOf<class AStructureSection>> AvailableSectionTypes;

	UPROPERTY(BlueprintReadOnly)
	TArray<TSubclassOf<class AStructureEquipment>> AvailableEquipmentTypes;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UUIBase> UIBase;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UStructureLayoutEditor> LayoutEditor;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCompatibleSectionSelect> SectionSelect;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> CloseButton;

	virtual void NativeConstruct() override;
	
	virtual void NativeOnActivated() override;

	virtual UWidget* NativeGetDesiredFocusTarget() const override;

	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	
public:
	
	UFUNCTION(BlueprintCallable)
	void SetParams(AStructure* NewTargetStructure, TArray<TSubclassOf<AStructureSection>> NewAvailableSectionTypes, TArray<TSubclassOf<AStructureEquipment>> NewAvailableEquipmentTypes);

	UFUNCTION(BlueprintCallable)
	void UpdateView();

	UFUNCTION(BlueprintCallable)
	TArray<TSubclassOf<AStructureSection>> GetAvailableSectionTypes();

	UFUNCTION(BlueprintCallable)
	UStructureSectionSlot* GetSelectedSectionSlot();
	
	UFUNCTION(BlueprintCallable)
	void SetSelectedSectionSlot(UStructureSectionSlot* NewSlot);

	UFUNCTION(BlueprintCallable)
	void AttachSectionType(TSubclassOf<AStructureSection> SectionType, FText SlotName);
	
	UFUNCTION(BlueprintCallable)
	void RemoveAttachedSection(UStructureSectionSlot* Target);

	UFUNCTION(BlueprintCallable)
	void DisconnectAttachedSection(UStructureSectionSlot* Target);

	UFUNCTION(BlueprintCallable)
	TArray<TSubclassOf<AStructureEquipment>> GetAvailableEquipmentTypes();
	
	UFUNCTION(BlueprintCallable)
	UStructureEquipmentSlot* GetSelectedEquipmentSlot();
	
	UFUNCTION(BlueprintCallable)
	void SetSelectedEquipmentSlot(UStructureEquipmentSlot* NewSlot);

	UFUNCTION(BlueprintCallable)
	void AttachEquipmentType(TSubclassOf<AStructureEquipment> EquipmentType, FText SlotName);

	UFUNCTION(BlueprintCallable)
	void RemoveAttachedEquipment(UStructureEquipmentSlot* Target);

private:

	UFUNCTION()
	void OnCloseButtonClicked();
	
	UFUNCTION()
	void OnCloseModalConfirmed();
	
};
