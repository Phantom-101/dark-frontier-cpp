// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Indications/DistanceIndication.h"
#include "Structures/Structure.h"

float UDistanceIndication::GetDistance() const
{
	AStructure* Player = Cast<AStructure>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if(IsValid(Player))
	{
		return (Player->GetActorLocation() - Structure->GetActorLocation()).Length();
	}

	return 0;
}
