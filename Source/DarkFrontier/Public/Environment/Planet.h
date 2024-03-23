// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Planet.generated.h"

UCLASS()
class DARKFRONTIER_API APlanet : public AActor
{
	GENERATED_BODY()
	
public:	

	APlanet();

protected:

	inline static TArray<FVector> OctVerts = { FVector::UpVector, FVector::LeftVector, FVector::BackwardVector, FVector::RightVector, FVector::ForwardVector, FVector::DownVector };
	
	inline static TArray<int> OctTris = { 0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 1, 5, 2, 1, 5, 3, 2, 5, 4, 3, 5, 1, 4 };

public:	

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<AActor> ReferenceActor;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	double PlanetRadius;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int MaxDepth;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int LeafDetail;

protected:
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TArray<TObjectPtr<class APlanetSurfaceNode>> Nodes;

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
