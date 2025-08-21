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
	FVector2D Pivot = FVector2D::ZeroVector;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FVector2D Fill = FVector2D::ZeroVector;

	virtual void NativePreConstruct() override;

public:

	UFUNCTION(BlueprintCallable)
	void SetBackgroundStyle(const TSubclassOf<UCommonBorderStyle>& InStyle);

	UFUNCTION(BlueprintCallable)
	void SetForegroundStyle(const TSubclassOf<UCommonBorderStyle>& InStyle);

	UFUNCTION(BlueprintCallable)
	void SetPivot(FVector2D InPivot);

	UFUNCTION(BlueprintCallable)
	void SetFill(FVector2D InFill);

	UFUNCTION(BlueprintCallable)
	void FillRect(const FVector2D& InStart, const FVector2D& InEnd);

	UFUNCTION(BlueprintCallable)
	void FillHorizontal(float InStart, float InEnd);

	UFUNCTION(BlueprintCallable)
	void FillVertical(float InStart, float InEnd);

private:

	void UpdateStyling() const;

	void UpdateFill() const;
	
};
