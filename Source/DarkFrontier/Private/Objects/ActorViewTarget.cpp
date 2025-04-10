// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/ActorViewTarget.h"

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

	// Use TransformVector here to get the view location offset relative to the actor location and not the world origin
	return Actor->GetActorLocation() + Actor->GetTransform().TransformVector(GetLocalBounds(Actor, true).Origin);
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
	
	return GetLocalBounds(Actor, true).SphereRadius * 2;
}

FBoxSphereBounds UActorViewTarget::GetLocalBounds(const AActor* Actor, const bool OnlyCollidingComponents)
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
