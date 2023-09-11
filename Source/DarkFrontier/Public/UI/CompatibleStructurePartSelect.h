// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "CompatibleStructurePartSelect.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UCompatibleStructurePartSelect : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UStructureBuilder> StructureBuilder;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonButtonBase> CloseButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonListView> TypeList;
	
	virtual void NativeConstruct() override;

public:

	void UpdateView() const;
	
private:

	void OnCloseButtonClicked() const;
	
};
