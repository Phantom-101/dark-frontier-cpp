// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Macros.h"
#include "UObject/Interface.h"
#include "Targetable.generated.h"

class AStructure;
class USelector;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DARKFRONTIER_API UTargetable : public UActorComponent
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<USelector> SelectorClass;

public:

	virtual bool IsTargetable(AStructure* Structure) const;

	TSubclassOf<USelector> GetSelectorClass() const;

};

UINTERFACE()
class UTargetableInterface : public UInterface
{
	GENERATED_BODY()
};

class ITargetableInterface
{
	GENERATED_BODY()

public:

	virtual UTargetable* GetTargetable() const = 0;

};
