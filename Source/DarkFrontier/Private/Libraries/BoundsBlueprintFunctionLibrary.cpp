// Fill out your copyright notice in the Description page of Project Settings.

#include "Libraries/BoundsBlueprintFunctionLibrary.h"
#include "Structures/Structure.h"

FBoxSphereBounds UBoundsBlueprintFunctionLibrary::GetBounds(const AActor* Actor, const bool OnlyCollidingComponents)
{
	const AStructure* Structure = Cast<AStructure>(Actor);
	return IsValid(Structure) ? GetStructureBounds(Structure, OnlyCollidingComponents) : GetActorBounds(Actor, OnlyCollidingComponents);
}

FBoxSphereBounds UBoundsBlueprintFunctionLibrary::GetActorBounds(const AActor* Actor, const bool OnlyCollidingComponents)
{
	FBoxSphereBounds Bounds(ForceInit);
	Actor->ForEachComponent<UPrimitiveComponent>(false, [&](const UPrimitiveComponent* InPrimComp)
	{
		if (InPrimComp->IsRegistered() && (!OnlyCollidingComponents || InPrimComp->IsCollisionEnabled()))
		{
			FBoxSphereBounds PrimBounds = InPrimComp->GetLocalBounds();
			PrimBounds.Origin = Actor->GetTransform().InverseTransformPosition(InPrimComp->GetComponentLocation());
			Bounds = Bounds + PrimBounds;
		}
	});
	return Bounds;
}

FBoxSphereBounds UBoundsBlueprintFunctionLibrary::GetStructureBounds(const AStructure* Structure, const bool OnlyCollidingComponents)
{
	FBoxSphereBounds Bounds(ForceInit);
	TArray<AActor*> AttachedActors;
	Structure->GetAttachedActors(AttachedActors);
	for (const AActor* AttachedActor : AttachedActors)
	{
		FBoxSphereBounds ActorBounds = GetBounds(AttachedActor, OnlyCollidingComponents);
		ActorBounds.Origin = Structure->GetTransform().InverseTransformPosition(AttachedActor->GetActorLocation());
		Bounds = Bounds + ActorBounds;
	}
	return Bounds;
}
