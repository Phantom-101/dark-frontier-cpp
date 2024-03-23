// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlanetSurfaceNode.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API APlanetSurfaceNode : public AActor
{
	GENERATED_BODY()

public:

	APlanetSurfaceNode();

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<class UProceduralMeshComponent> ProceduralMesh;
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TArray<TObjectPtr<APlanetSurfaceNode>> SubNodes;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	bool IsLeaf;
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<class APlanet> Planet;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	FVector A;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	FVector B;
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	FVector C;
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	int NodeHeight;

public:

	virtual void Tick(float DeltaTime) override;

	void Init(APlanet* InPlanet, const FVector& InA, const FVector& InB, const FVector& InC, int InHeight);

protected:

	void UpdateLeafStatus();

	void Generate();

	void Clean();

	void GenerateAsLeaf();

	void GenerateAsBranch();

	int ToIndex(int I, int J);

	FVector ToSampled(const FVector& InPoint) const;
	
	FVector ToSphere(const FVector& InPoint) const;

	FVector ToHeight(const FVector& InPoint, double InHeight) const;
	
	double Sample(FVector InPoint) const;
	
};
