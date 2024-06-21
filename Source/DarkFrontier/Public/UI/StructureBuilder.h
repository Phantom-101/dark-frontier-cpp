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
	TObjectPtr<class UStructureSlot> SelectedSlot;

	UPROPERTY(BlueprintReadOnly)
	TArray<TSubclassOf<class AStructurePart>> AvailableParts;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UUIBase> UIBase;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UStructureLayoutEditor> LayoutEditor;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCompatibleStructurePartSelect> PartSelect;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> CloseButton;

	virtual void NativeConstruct() override;
	
	virtual void NativeOnActivated() override;

	virtual UWidget* NativeGetDesiredFocusTarget() const override;

	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	
public:
	
	UFUNCTION(BlueprintCallable)
	void SetParams(AStructure* NewTargetStructure, TArray<TSubclassOf<AStructurePart>> InAvailableParts);

	UFUNCTION(BlueprintCallable)
	void UpdateView() const;

	UFUNCTION(BlueprintCallable)
	TArray<TSubclassOf<AStructurePart>> GetAvailableParts();

	UFUNCTION(BlueprintCallable)
	UStructureSlot* GetSelectedSlot() const;
	
	UFUNCTION(BlueprintCallable)
	void SetSelectedSlot(UStructureSlot* NewSlot);

	UFUNCTION(BlueprintCallable)
	void AttachPart(TSubclassOf<AStructurePart> PartType, FText SlotName);
	
	UFUNCTION(BlueprintCallable)
	void RemovePart(UStructureSlot* Target) const;

	UFUNCTION(BlueprintCallable)
	void DisconnectPart(UStructureSlot* Target) const;

private:

	UFUNCTION()
	void OnCloseButtonClicked();
	
	UFUNCTION()
	void OnCloseModalConfirmed();
	
};
