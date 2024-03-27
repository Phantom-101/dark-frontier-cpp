// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "Structure.h"
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
	TObjectPtr<UInputAction> EditStructureAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="UI")
	TSubclassOf<class UUIBase> UIBaseClass;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="UI")
	TSubclassOf<class UCommonActivatableWidget> GameUIClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="UI")
	TSubclassOf<UCommonActivatableWidget> StructureDetailsUIClass;

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
	TObjectPtr<AActor> LookTarget;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Camera")
	FVector2D LookRotation;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Camera")
	float ZoomLevel = 2.5;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<TSubclassOf<class AStructurePart>> AvailableParts;

public:
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="UI")
	TObjectPtr<UUIBase> UIBaseWidget;

	FStructureStateChanged OnLayoutChanged;

	FStructureStateChanged OnActionsChanged;

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnPossess(APawn* InPawn) override;
	
	virtual void OnUnPossess() override;

	UFUNCTION(BlueprintCallable, Category="Camera")
	void UpdateCamera();

	UFUNCTION(BlueprintCallable, Category="Camera")
	FBoxSphereBounds GetViewBounds(const AActor* Actor, const bool OnlyCollidingComponents);

	UFUNCTION(BlueprintCallable, Category="Camera")
	FBoxSphereBounds GetStructureViewBounds(const AStructure* Structure, const bool OnlyCollidingComponents);

public:
	
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
	void EditStructure(const FInputActionInstance& Instance);

	UFUNCTION()
	void PropagateLayoutChange();

	UFUNCTION()
	void PropagateActionsChange();
};
