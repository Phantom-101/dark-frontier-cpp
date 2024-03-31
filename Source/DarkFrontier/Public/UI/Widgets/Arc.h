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
	float ArcStart;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float ArcLength;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FLinearColor ArcColor;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> MaterialInstance;

	virtual void NativePreConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	void SetLength(float Start, float Length);

	void SetEndpoints(float Start, float End);

	void SetColor(FLinearColor InColor);
	
};
