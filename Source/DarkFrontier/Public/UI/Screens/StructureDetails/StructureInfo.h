// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StructureInfo.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UStructureInfo : public UCommonUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> NameText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UInfoField> HullField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> ShieldField;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> EnergyField;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> UpkeepField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> LinearField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UInfoField> AngularField;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> TypeModeButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> ListModeButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UWidgetSwitcher> PartListSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UScrollBox> TypeList;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonListView> PartCardList;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class UStructurePartSlotListView> ListViewClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class UCommonButtonStyle> SelectedStyle;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UCommonButtonStyle> UnSelectedStyle;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<class UStructureDetails> Screen;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<class AStructure> TargetStructure;

	virtual void NativeConstruct() override;

public:

	void SetTarget(AStructure* InTargetStructure);

private:

	void TypeModeSelected();

	void ListModeSelected();
	
	static inline FString ToString(float Value);

	static inline FText ToText(const FString& String);
	
};
