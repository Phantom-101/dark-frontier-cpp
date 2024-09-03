// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureFacility.h"
#include "Components/ActorComponent.h"
#include "StructureProduction.generated.h"

class AStructure;
class AStructurePart;
class URecipe;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DARKFRONTIER_API UStructureProduction : public UStructureFacility
{
	GENERATED_BODY()

public:

	UStructureProduction();

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<URecipe> Recipe;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	bool RequirementsMet = false;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	float Progress = 0;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	float InputValue = 0;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
