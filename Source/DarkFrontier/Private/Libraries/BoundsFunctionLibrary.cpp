// Fill out your copyright notice in the Description page of Project Settings.

#include "Libraries/BoundsFunctionLibrary.h"

FBoxSphereBounds UBoundsFunctionLibrary::GetLocalBounds(const AActor* Actor, const bool OnlyCollidingComponents)
{
	FBoxSphereBounds Bounds(ForceInit);

	Actor->ForEachComponent<UPrimitiveComponent>(true, [&](const UPrimitiveComponent* PrimComp)
	{
		if(PrimComp->IsRegistered() && (!OnlyCollidingComponents || PrimComp->IsCollisionEnabled()))
		{
			FBoxSphereBounds PrimBounds = PrimComp->GetLocalBounds();
			// Convert component location from world space to actor space
			PrimBounds.Origin += Actor->GetTransform().InverseTransformPosition(PrimComp->GetComponentLocation());
			Bounds = Bounds + PrimBounds;
		}
	});

	TArray<AActor*> AttachedActors;
	Actor->GetAttachedActors(AttachedActors);
	for(const AActor* AttachedActor : AttachedActors)
	{
		FBoxSphereBounds ActorBounds = GetLocalBounds(AttachedActor, OnlyCollidingComponents);
		// Convert attached actor location from world space to actor space
		ActorBounds.Origin += Actor->GetTransform().InverseTransformPosition(AttachedActor->GetActorLocation());
		Bounds = Bounds + ActorBounds;
	}

	return Bounds;
}
