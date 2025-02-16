// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "FillBar.generated.h"

class UCommonBorderStyle;
class USizeBox;
class UCommonBorder;
/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UFillBar : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonBorder> Background;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonBorder> Foreground;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UCommonBorderStyle> BackgroundStyle;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UCommonBorderStyle> ForegroundStyle;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FVector2D Start = FVector2D::ZeroVector;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FVector2D Fill = FVector2D::ZeroVector;

	virtual void NativePreConstruct() override;

public:

	void SetBackgroundStyle(const TSubclassOf<UCommonBorderStyle>& InStyle);

	void SetForegroundStyle(const TSubclassOf<UCommonBorderStyle>& InStyle);

	void SetStart(FVector2D InStart);

	void SetFill(FVector2D InFill);

private:

	void UpdateStyling() const;

	void UpdateFill() const;
	
};
