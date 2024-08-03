// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "InfoField.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UInfoField : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UImage> IconImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> LabelText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> ContentText;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UTexture2D> Icon;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText Label;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText Content;

	virtual void NativePreConstruct() override;

public:

	void SetContent(const FText& InContent) const;

	void SetContentFromString(const FString& InContent) const;

	void SetContentFromInt(int InContent) const;

	void SetContentFromFloat(float InContent) const;
	
};
