// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/Timestamp.h"

FTimestamp::FTimestamp()
{
	Value = 0;
}

FTimestamp::FTimestamp(const float InValue)
{
	Value = InValue;
}

FTimestamp FTimestamp::Difference(const FTimestamp Other) const
{
	return FTimestamp(FMath::Abs(Value - Other.Value));
}
