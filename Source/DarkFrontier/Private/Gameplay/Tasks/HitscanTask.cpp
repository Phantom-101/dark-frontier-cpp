// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Tasks/HitscanTask.h"
#include "Structures/StructurePart.h"

UHitscanTask* UHitscanTask::New(UGameplayAbility* OwningAbility, const FVector& InStart, const FVector& InEnd, const ECollisionChannel InChannel, const TArray<AActor*>& InIgnored)
{
	UHitscanTask* Task = NewAbilityTask<UHitscanTask>(OwningAbility);
	Task->StartLocation = InStart;
	Task->EndLocation = InEnd;
	Task->TraceChannel = InChannel;
	Task->IgnoredActors = InIgnored;
	return Task;
}

void UHitscanTask::Activate()
{
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(IgnoredActors);

	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, TraceChannel, QueryParams);
	HitPart = Cast<AStructurePart>(HitResult.GetActor());

	Super::Activate();
}
