// Fill out your copyright notice in the Description page of Project Settings.

#include "Environment/Planet.h"
#include "Environment/PlanetSurfaceNode.h"

APlanet::APlanet()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlanet::BeginPlay()
{
	Super::BeginPlay();

	for(int i = 0; i < 8; i++)
	{
		Nodes.Add(GetWorld()->SpawnActor<APlanetSurfaceNode>());
		Nodes[i]->SetActorLocation(GetActorLocation());
		Nodes[i]->Init(this, OctVerts[OctTris[i * 3]], OctVerts[OctTris[i * 3 + 1]], OctVerts[OctTris[i * 3 + 2]], MaxDepth);
	}
}

void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

