// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "StructureDamageType.h"
#include "SimpleDamageType.generated.h"

class UTargetGroup;
/**
 * 
 */
UCLASS()
class DARKFRONTIER_API USimpleDamageType : public UStructureDamageType
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<TObjectPtr<UTargetGroup>, FGameplayAttribute> ResistanceAttributes;

public:

	virtual float Evaluate(const UTargetGroup* TargetGroup, const UAbilitySystemComponent* Comp) const override;
	
};
