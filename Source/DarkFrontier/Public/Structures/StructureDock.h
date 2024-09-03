// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureFacility.h"
#include "Components/ActorComponent.h"
#include "StructureDock.generated.h"

class AStructurePart;
class AStructure;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DARKFRONTIER_API UStructureDock : public UStructureFacility
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<AStructure> Docker;

public:

	UFUNCTION(BlueprintCallable)
	bool ConfirmDock(AStructure* Structure);

	UFUNCTION(BlueprintCallable)
	bool ConfirmUnDock(AStructure* Structure);
	
};
