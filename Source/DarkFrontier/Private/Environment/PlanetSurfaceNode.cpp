// Fill out your copyright notice in the Description page of Project Settings.

#include "Environment/PlanetSurfaceNode.h"
#include "ProceduralMeshComponent.h"
#include "Environment/Planet.h"

APlanetSurfaceNode::APlanetSurfaceNode()
{
	PrimaryActorTick.bCanEverTick = true;

	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMesh");
	SetRootComponent(ProceduralMesh);
}

void APlanetSurfaceNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsValid(Planet))
	{
		UpdateLeafStatus();
	}
}

void APlanetSurfaceNode::Init(APlanet* InPlanet, const FVector& InA, const FVector& InB, const FVector& InC, int InHeight)
{
	Planet = InPlanet;
	A = InA;
	B = InB;
	C = InC;
	NodeHeight = InHeight;

	UpdateLeafStatus();
	Generate();
}

void APlanetSurfaceNode::UpdateLeafStatus()
{
	const FVector SampledA = ToSampled(A);
	const FVector SampledB = ToSampled(B);
	const FVector SampledC = ToSampled(C);
	const double SideLength = (SampledA - SampledB).Length();
	//const double CameraDist = ((A + B + C) / 3 - GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation()).Length();
	const double CameraDist = ((SampledA + SampledB + SampledC) / 3 + Planet->GetActorLocation() - Planet->ReferenceActor->GetActorLocation()).Length();
	const bool NewIsLeaf = NodeHeight == 0 || CameraDist > SideLength;
	if(NewIsLeaf != IsLeaf)
	{
		IsLeaf = NewIsLeaf;
		Generate();
	}
}

void APlanetSurfaceNode::Generate()
{
	Clean();
	if(IsLeaf)
	{
		GenerateAsLeaf();
	}
	else
	{
		GenerateAsBranch();
	}
}

void APlanetSurfaceNode::Clean()
{
	for(APlanetSurfaceNode* SubNode : SubNodes)
	{
		SubNode->Clean();
		SubNode->Destroy();
	}
	SubNodes.Empty();

	ProceduralMesh->ClearMeshSection(0);
}

void APlanetSurfaceNode::GenerateAsLeaf()
{
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	const TArray<FVector> Normals;
	const TArray<FVector2D> UV0;
	const TArray<FLinearColor> VertexColors;
	const TArray<FProcMeshTangent> Tangents;
	
	const FVector AB = (B - A) / (Planet->LeafDetail + 1);
	const FVector BC = (C - B) / (Planet->LeafDetail + 1);
	for(int i = 0; i <= Planet->LeafDetail + 1; i++)
	{
		for(int j = 0; j <= i; j++)
		{
			const FVector Current = A + AB * i + BC * j;
			Vertices.Add(ToSampled(Current));
			if(j <= i - 2)
			{
				Triangles.Add(ToIndex(i, j + 1));
				Triangles.Add(ToIndex(i - 1, j + 1));
				Triangles.Add(ToIndex(i - 1, j));
			}
			if(j <= i - 1)
			{
				Triangles.Add(ToIndex(i, j));
				Triangles.Add(ToIndex(i, j + 1));
				Triangles.Add(ToIndex(i - 1, j));
			}
		}
	}

	ProceduralMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UV0, VertexColors, Tangents, true);
}

void APlanetSurfaceNode::GenerateAsBranch()
{
	const FVector AB = (A + B) / 2;
	const FVector BC = (B + C) / 2;
	const FVector AC = (A + C) / 2;
	SubNodes.Add(GetWorld()->SpawnActor<APlanetSurfaceNode>());
	SubNodes[0]->SetActorLocation(GetActorLocation());
	SubNodes[0]->Init(Planet, A, AB, AC, NodeHeight - 1);
	
	SubNodes.Add(GetWorld()->SpawnActor<APlanetSurfaceNode>());
	SubNodes[1]->SetActorLocation(GetActorLocation());
	SubNodes[1]->Init(Planet, B, BC, AB, NodeHeight - 1);
	
	SubNodes.Add(GetWorld()->SpawnActor<APlanetSurfaceNode>());
	SubNodes[2]->SetActorLocation(GetActorLocation());
	SubNodes[2]->Init(Planet, C, AC, BC, NodeHeight - 1);
	
	SubNodes.Add(GetWorld()->SpawnActor<APlanetSurfaceNode>());
	SubNodes[3]->SetActorLocation(GetActorLocation());
	SubNodes[3]->Init(Planet, AB, BC, AC, NodeHeight - 1);
}

int APlanetSurfaceNode::ToIndex(const int I, const int J)
{
	const int Total = (I + 1) * (I + 2) / 2;
	const int FromEnd = I - J;
	return Total - FromEnd - 1;
}

FVector APlanetSurfaceNode::ToSampled(const FVector& InPoint) const
{
	const FVector OnSphere = ToSphere(InPoint);
	return ToHeight(OnSphere, Planet->PlanetRadius + Sample(OnSphere));
}

FVector APlanetSurfaceNode::ToSphere(const FVector& InPoint) const
{
	return ToHeight(InPoint, Planet->PlanetRadius);
}

FVector APlanetSurfaceNode::ToHeight(const FVector& InPoint, const double InHeight) const
{
	FVector Norm = InPoint;
	Norm.Normalize();
	return Norm * InHeight;
}

double APlanetSurfaceNode::Sample(FVector InPoint) const
{
	return 0;
}
