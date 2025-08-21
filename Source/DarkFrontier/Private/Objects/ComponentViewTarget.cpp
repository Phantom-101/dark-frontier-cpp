// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/ComponentViewTarget.h"

UComponentViewTarget* UComponentViewTarget::New(USceneComponent* Component)
{
	UComponentViewTarget* ViewTarget = NewObject<UComponentViewTarget>();
	ViewTarget->Component = Component;
	return ViewTarget;
}

bool UComponentViewTarget::IsValid()
{
	return ::IsValid(Component);
}

FVector UComponentViewTarget::GetViewLocation()
{
	if(!IsValid())
	{
		return Super::GetViewLocation();
	}

	// Use TransformVector to get the view location origin offset in world space
	const FVector Origin = Component->GetLocalBounds().Origin;
	return Component->GetComponentLocation() + Component->GetComponentTransform().TransformVector(Origin);
}

FRotator UComponentViewTarget::GetViewRotation()
{
	if(!IsValid())
	{
		return Super::GetViewRotation();
	}

	return Component->GetComponentRotation();
}

double UComponentViewTarget::GetViewDistance()
{
	if(!IsValid())
	{
		return Super::GetViewDistance();
	}

	return Component->GetLocalBounds().SphereRadius * 2;
}
