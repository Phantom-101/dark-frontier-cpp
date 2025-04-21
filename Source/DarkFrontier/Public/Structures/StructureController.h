// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "Structure.h"
#include "StructureLayout.h"
#include "StructureController.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API AStructureController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AStructureController();

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> RotateAddAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> RotateOverrideAction;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> ZoomAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> ToggleUnlockAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> InventoryAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> EditStructureAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="UI")
	TSubclassOf<class UUIBase> UIBaseClass;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="UI")
	TSubclassOf<class UGameUI> GameUIClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="UI")
	TSubclassOf<class UInventoryUI> InventoryUIClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="UI")
	TSubclassOf<class UBuildUI> BuildUIClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="UI")
	TSubclassOf<class UStationUI> StationUIClass;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Controller")
	TObjectPtr<class AStructure> StructurePawn;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Input")
	FVector MoveInput;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Input")
	FVector RotateAddInput;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Input")
	FVector RotateOverrideInput;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Input")
	bool IsCursorUnlocked = false;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Camera")
	TObjectPtr<UViewTarget> ViewTarget;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Camera")
	FVector2D CameraRotation;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Camera")
	float ZoomLevel = 2;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<TSubclassOf<class AStructurePart>> AvailableParts;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="UI")
	TObjectPtr<UUIBase> UIBaseWidget;

public:

	FStructureLayoutChanged OnLayoutChanged;

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnPossess(APawn* InPawn) override;
	
	virtual void OnUnPossess() override;

public:

	UFUNCTION(BlueprintCallable, Category="Camera")
	void SetViewTarget(UViewTarget* InTarget);

protected:

	UFUNCTION(BlueprintCallable, Category="Camera")
	void UpdateCamera();

public:

	UFUNCTION(BlueprintCallable, Category="UI")
	UUIBase* GetUIBaseWidget() const;
	
	UFUNCTION(BlueprintCallable, Category="UI")
	FVector GetTurnIndicatorOffset() const;

protected:
	
	UFUNCTION()
	void Move(const FInputActionInstance& Instance);

	UFUNCTION()
	void RotateAdd(const FInputActionInstance& Instance);

	UFUNCTION()
	void RotateOverride(const FInputActionInstance& Instance);

	UFUNCTION()
	void Look(const FInputActionInstance& Instance);

	UFUNCTION()
	void Zoom(const FInputActionInstance& Instance);

	UFUNCTION()
	void ToggleUnlock(const FInputActionInstance& Instance);

	UFUNCTION()
	void OpenInventory(const FInputActionInstance& Instance);

	UFUNCTION()
	void EditStructure(const FInputActionInstance& Instance);

	UFUNCTION()
	void PropagateLayoutChange() const;

private:

	void HandleDock(UStructureDock* Dock) const;
	
};
