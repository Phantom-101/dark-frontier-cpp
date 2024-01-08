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

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> InputMapping;

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
	TSubclassOf<UCommonActivatableWidget> StructureBuilderUIClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<TSubclassOf<class AStructurePart>> AvailableParts;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TObjectPtr<class AStructure> StructurePawn;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TObjectPtr<UUIBase> UIBaseWidget;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	bool IsCursorUnlocked;

	FStructureStateChanged OnLayoutChanged;

	FStructureStateChanged OnActionsChanged;

protected:
	
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

public:

	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionInstance& Instance);

	UFUNCTION(BlueprintCallable)
	void RotateAdd(const FInputActionInstance& Instance);

	UFUNCTION(BlueprintCallable)
	void RotateOverride(const FInputActionInstance& Instance);

	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionInstance& Instance);

	UFUNCTION(BlueprintCallable)
	void Zoom(const FInputActionInstance& Instance);

	UFUNCTION(BlueprintCallable)
	void ToggleUnlock(const FInputActionInstance& Instance);
	
	UFUNCTION(BlueprintCallable)
	void EditStructure(const FInputActionInstance& Instance);

	UFUNCTION(BlueprintCallable)
	void PropagateLayoutChange();

	UFUNCTION(BlueprintCallable)
	void PropagateActionsChange();
};
