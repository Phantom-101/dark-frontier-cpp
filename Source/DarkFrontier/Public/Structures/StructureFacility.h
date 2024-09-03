// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "StructureFacility.generated.h"

class AStructurePart;
class AStructure;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DARKFRONTIER_API UStructureFacility : public USceneComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<AStructurePart> OwningPart;

	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	AStructure* GetOwningStructure() const;

	UFUNCTION(BlueprintCallable)
	AStructurePart* GetOwningPart() const;

};
