// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/ActorViewTarget.h"
#include "Libraries/BoundsFunctionLibrary.h"

UActorViewTarget* UActorViewTarget::New(AActor* Actor)
{
	UActorViewTarget* ViewTarget = NewObject<UActorViewTarget>();
	ViewTarget->Actor = Actor;
	return ViewTarget;
}

bool UActorViewTarget::IsValid()
{
	return ::IsValid(Actor);
}

FVector UActorViewTarget::GetViewLocation()
{
	if(!IsValid())
	{
		return Super::GetViewLocation();
	}

	// Use TransformVector to get the view location origin offset in world space
	const FVector Origin = UBoundsFunctionLibrary::GetLocalBounds(Actor, true).Origin;
	return Actor->GetActorLocation() + Actor->GetTransform().TransformVector(Origin);
}

FRotator UActorViewTarget::GetViewRotation()
{
	if(!IsValid())
	{
		return Super::GetViewRotation();
	}

	return Actor->GetActorRotation();
}

double UActorViewTarget::GetViewDistance()
{
	if(!IsValid())
	{
		return Super::GetViewDistance();
	}
	
	return UBoundsFunctionLibrary::GetLocalBounds(Actor, true).SphereRadius * 2;
}
