// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SectorLocation.h"
#include "GameFramework/Actor.h"
#include "Structures/Targetable.h"
#include "Portal.generated.h"

class USphereComponent;
class UTargetable;
class USectorLocation;

UCLASS()
class DARKFRONTIER_API APortal : public AActor, public ISectorLocationInterface, public ITargetableInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<USphereComponent> Trigger;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<USectorLocation> Location;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UTargetable> Targetable;

	// Use actor pointer as components need FComponentReference workaround
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<AActor> Destination;

public:

	APortal();

protected:

	virtual void Tick(float DeltaSeconds) override;

public:

	virtual USectorLocation* GetSectorLocation() const override;

	virtual UTargetable* GetTargetable() const override;

private:

	void Transfer(const TObjectPtr<USectorLocation>& User) const;

};
