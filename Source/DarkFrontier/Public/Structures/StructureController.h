// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> RotateAddAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> RotateOverrideAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> UnlockCursorAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> EditStructureAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<class UUIBase> UIBaseClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<class UCommonActivatableWidget> GameUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UCommonActivatableWidget> StructureBuilderUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class AStructureSection>> AvailableSectionTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class AStructureEquipment>> AvailableEquipmentTypes;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UUIBase> UIBaseWidget;

protected:
	
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaSeconds) override;

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
	void UnlockCursor(const FInputActionInstance& Instance);
	
	UFUNCTION(BlueprintCallable)
	void EditStructure(const FInputActionInstance& Instance);
};
