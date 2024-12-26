// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Arc.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UArc : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UImage> ArcImage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UMaterialInterface> ArcMaterial;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float ArcThickness = 0.1;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float ArcStart = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float ArcLength = 0.25;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FLinearColor ArcColor;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> MaterialInstance;

	virtual void NativePreConstruct() override;

public:

	void SetThickness(float InThickness);

	void SetLength(float Length);

	void SetStartAndLength(float Start, float Length);

	void SetEndpoints(float Start, float End);

	void SetColor(FLinearColor InColor);

protected:

	void UpdateArc() const;
	
};
