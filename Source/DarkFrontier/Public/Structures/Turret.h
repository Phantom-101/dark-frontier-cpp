// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "Structures/StructurePart.h"
#include "Turret.generated.h"

class UTurretSource;
class UTurretAbility;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ATurret : public AStructurePart
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Turret")
	TArray<TObjectPtr<UTurretSource>> Sources;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	FGameplayTag PayloadTag;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Gameplay")
	FGameplayAbilitySpecHandle AbilityHandle;

	virtual void BeginPlay() override;

public:

	virtual void OnRegistered() override;

	virtual void OnUnRegistered() override;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual TSubclassOf<UTurretAbility> GetAbilityClass();

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual bool CanActivate();

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual void TryActivate();

protected:

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual bool CanActivateSource(UTurretSource* Source);

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual bool TryActivateSource(UTurretSource* Source);

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void SendPayload(FGameplayTag Tag, UObject* Obj) const;
	
};
