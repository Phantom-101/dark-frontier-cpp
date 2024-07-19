// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StructureDock.generated.h"

class AStructurePart;
class AStructure;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DARKFRONTIER_API UStructureDock : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<AStructurePart> OwningPart;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<AStructure> Docker;

	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	AStructure* GetOwningStructure() const;

	UFUNCTION(BlueprintCallable)
	AStructurePart* GetOwningPart() const;

	UFUNCTION(BlueprintCallable)
	bool TryDock(AStructure* Structure);

	UFUNCTION(BlueprintCallable)
	bool TryUnDock();
	
};
