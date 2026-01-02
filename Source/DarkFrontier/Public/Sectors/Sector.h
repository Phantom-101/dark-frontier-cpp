// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sector.generated.h"

class APortal;
class USectorRoot;
class USectorLocation;
class UTargetable;
class AItemPod;
class AAsteroid;
class AStructure;

UCLASS()
class DARKFRONTIER_API ASector : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<USectorRoot> Root;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FVector2D Position = FVector2D::ZeroVector;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FLinearColor Color = FLinearColor::White;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TSet<TObjectPtr<USectorLocation>> Locations;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TSet<TObjectPtr<AStructure>> Structures;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TSet<TObjectPtr<AAsteroid>> Asteroids;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TSet<TObjectPtr<AItemPod>> ItemPods;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TSet<TObjectPtr<APortal>> Portals;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TSet<TObjectPtr<UTargetable>> Targets;

public:

	ASector();

	const FVector2D& GetPosition() const;

	const FLinearColor& GetColor() const;

	const TSet<TObjectPtr<UTargetable>>& GetTargets() const;

	TSet<TObjectPtr<ASector>> GetConnections() const;

	UFUNCTION(BlueprintCallable)
	void Register(USectorLocation* Location);

	UFUNCTION(BlueprintCallable)
	void Unregister(USectorLocation* Location);

};
