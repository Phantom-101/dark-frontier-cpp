// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StructureFacility.generated.h"

class AStructure;
class AStructurePart;
class URecipe;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DARKFRONTIER_API UStructureFacility : public UActorComponent
{
	GENERATED_BODY()

public:

	UStructureFacility();

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<TObjectPtr<URecipe>> AllowedRecipes;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<AStructurePart> OwningPart;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TObjectPtr<URecipe> CurrentRecipe;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	bool RequirementsMet = false;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	float Progress = 0;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	float InputValue = 0;

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UFUNCTION(BlueprintCallable)
	AStructure* GetOwningStructure() const;

	UFUNCTION(BlueprintCallable)
	AStructurePart* GetOwningPart() const;
	
};
