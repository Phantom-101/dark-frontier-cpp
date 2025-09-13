// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Turret.h"
#include "TractorBeam.generated.h"

UCLASS()
class DARKFRONTIER_API ATractorBeam : public ATurret
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float TractorForce = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float TractorRange = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float CollectionRange = 0;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UTargetable> Target;

public:

	ATractorBeam();

	bool IsActivated() const;

	virtual bool CanActivate(UTargetable* InTarget) const override;

protected:

	virtual void OnActivate(UTargetable* InTarget) override;

public:

	bool CanDeactivate() const;

	void TryDeactivate();

	virtual void Tick(float DeltaSeconds) override;

private:

	FVector GetForce() const;

};
