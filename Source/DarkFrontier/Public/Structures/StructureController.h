// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "Structure.h"
#include "StructureLayout.h"
#include "StructureController.generated.h"

class UViewTarget;

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
	TObjectPtr<UInputAction> InfoAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> EditStructureAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="UI")
	TSubclassOf<class UScreens> ScreensClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="UI")
	TSubclassOf<class UGameScreens> GameScreensClass;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="UI")
	TSubclassOf<class UFlightScreen> FlightScreenClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="UI")
	TSubclassOf<class UInventoryScreen> InventoryScreenClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="UI")
	TSubclassOf<class UInfoScreen> InfoScreenClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="UI")
	TSubclassOf<class UBuildScreen> BuildScreenClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="UI")
	TSubclassOf<class UStationScreen> StationScreenClass;

	// TODO add faction

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

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Gameplay")
	TObjectPtr<UTargetable> SelectTarget;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Camera")
	TObjectPtr<UViewTarget> ViewTarget;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Camera")
	FVector2D CameraRotation;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Camera")
	float ZoomLevel = 2;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<TSubclassOf<class AStructurePart>> AvailableParts;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="UI")
	TObjectPtr<UScreens> Screens;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="UI")
	TObjectPtr<UGameScreens> GameScreens;

public:

	FStructureLayoutChanged OnLayoutChanged;

	FSectorChanged OnSectorChanged;

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnPossess(APawn* InPawn) override;
	
	virtual void OnUnPossess() override;

public:

	UFUNCTION(BlueprintPure, Category="Gameplay")
	UTargetable* GetSelectTarget() const;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void SetSelectTarget(UTargetable* InSelectTarget);

	UFUNCTION(BlueprintCallable, Category="Camera")
	void SetViewTarget(UViewTarget* InTarget);

	UFUNCTION(BlueprintCallable)
	bool GetIsCursorUnlocked() const;

protected:

	UFUNCTION(BlueprintCallable, Category="Camera")
	void UpdateCamera();

public:

	UFUNCTION(BlueprintCallable, Category="UI")
	UScreens* GetScreens() const;
	
	UFUNCTION(BlueprintCallable, Category="UI")
	UGameScreens* GetGameScreens() const;
	
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
	void Info(const FInputActionInstance& Instance);

	UFUNCTION()
	void EditStructure(const FInputActionInstance& Instance);

	UFUNCTION()
	void PropagateLayoutChange() const;

	UFUNCTION()
	void PropagateSectorChange(ASector* Sector);

private:

	void HandleDock(UStructureDock* Dock) const;
	
};
