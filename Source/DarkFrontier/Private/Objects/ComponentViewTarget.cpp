// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/ComponentViewTarget.h"

FVector UComponentViewTarget::GetViewLocation()
{
	if(Component == nullptr)
	{
		return FVector::ZeroVector;
	}

	// Use TransformVector here to get the view location offset relative to the actor location and not the world origin
	return Component->GetComponentLocation() + Component->GetComponentTransform().TransformVector(Component->GetLocalBounds().Origin);
}

FRotator UComponentViewTarget::GetViewRotation()
{
	if(Component == nullptr)
	{
		return FRotator::ZeroRotator;
	}

	return Component->GetComponentRotation();
}

double UComponentViewTarget::GetViewDistance()
{
	if(Component == nullptr)
	{
		return 0;
	}

	return Component->GetLocalBounds().SphereRadius * 2;
}
