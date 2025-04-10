// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/ViewTarget.h"

FVector IViewTarget::GetViewLocation()
{
	const AActor* Actor = Cast<AActor>(this);
	if(Actor == nullptr)
	{
		return FVector::ZeroVector;
	}

	// Use TransformVector here to get the view location offset relative to the actor location and not the world origin
	return Actor->GetActorLocation() + Actor->GetTransform().TransformVector(GetLocalBounds(Actor, true).Origin);
}

FRotator IViewTarget::GetViewRotation()
{
	const AActor* Actor = Cast<AActor>(this);
	if(Actor == nullptr)
	{
		return FRotator::ZeroRotator;
	}

	return Actor->GetActorRotation();
}

double IViewTarget::GetViewDistance()
{
	const AActor* Actor = Cast<AActor>(this);
	if(Actor == nullptr)
	{
		return 0;
	}
	
	return GetLocalBounds(Actor, true).SphereRadius * 2;
}

FBoxSphereBounds IViewTarget::GetLocalBounds(const AActor* Actor, const bool OnlyCollidingComponents)
{
	FBoxSphereBounds Bounds(ForceInit);

	Actor->ForEachComponent<UPrimitiveComponent>(true, [&](const UPrimitiveComponent* PrimComp)
	{
		if (PrimComp->IsRegistered() && (!OnlyCollidingComponents || PrimComp->IsCollisionEnabled()))
		{
			FBoxSphereBounds PrimBounds = PrimComp->GetLocalBounds();
			// Use InverseTransformPosition here as component location is relative to world origin and not actor location
			PrimBounds.Origin += Actor->GetTransform().InverseTransformPosition(PrimComp->GetComponentLocation());
			Bounds = Bounds + PrimBounds;
		}
	});

	TArray<AActor*> AttachedActors;
	Actor->GetAttachedActors(AttachedActors);
	for (const AActor* AttachedActor : AttachedActors)
	{
		FBoxSphereBounds ActorBounds = GetLocalBounds(AttachedActor, OnlyCollidingComponents);
		// Use InverseTransformPosition here as component location is relative to world origin and not actor location
		ActorBounds.Origin += Actor->GetTransform().InverseTransformPosition(AttachedActor->GetActorLocation());
		Bounds = Bounds + ActorBounds;
	}

	return Bounds;
}
