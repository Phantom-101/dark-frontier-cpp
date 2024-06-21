// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "Structures/StructurePart.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ATurret : public AStructurePart
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Turret")
	TArray<TObjectPtr<USceneComponent>> SourceTransforms;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TSubclassOf<class UTurretAbility> Ability;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	FGameplayTag PayloadTag;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	FGameplayAbilitySpecHandle AbilityHandle;

public:

	virtual void OnRegistered() override;

	virtual void OnUnRegistered() override;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	int TryActivate();

protected:

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual void OnActivated(int Activated);

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual bool CanActivateSource(USceneComponent* SourceTransform);

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual void ActivateSource(USceneComponent* SourceTransform);

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void SendPayload(FGameplayTag Tag, UObject* Obj) const;
	
};
