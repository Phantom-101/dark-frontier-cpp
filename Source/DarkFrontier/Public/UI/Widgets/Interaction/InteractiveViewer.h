// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "InteractiveViewer.generated.h"

class UCommonButtonBase;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UInteractiveViewer : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> ResetButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> ZoomInButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> ZoomOutButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UNamedSlot> ContentSlot;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float ZoomFactor = 1.5;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	int ZoomLevel = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int MaxZoomLevel = 5;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int MinZoomLevel = -5;

	virtual void NativeConstruct() override;

public:

	UFUNCTION(BlueprintCallable)
	void Reset();

	UFUNCTION(BlueprintCallable)
	void ZoomIn();

	UFUNCTION(BlueprintCallable)
	void ZoomOut();

protected:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

private:

	FVector2D GetCenter() const;

	void UpdateZoom(const FVector2D& Focal) const;

	float GetScaleFactor() const;

	UFUNCTION()
	void HandlePan(UDragDropOperation* Operation);
	
};

UCLASS()
class DARKFRONTIER_API UPanOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	FVector2D CursorDelta;

protected:

	virtual void Dragged_Implementation(const FPointerEvent& PointerEvent) override;
	
};
