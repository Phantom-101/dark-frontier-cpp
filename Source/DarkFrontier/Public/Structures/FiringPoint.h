// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FiringPoint.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKFRONTIER_API UFiringPoint : public USceneComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class ATurret> OwningTurret;

	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable, Category="Turret")
	ATurret* GetOwningTurret() const;
	
};
