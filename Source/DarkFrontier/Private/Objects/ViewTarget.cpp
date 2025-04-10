// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/ViewTarget.h"

bool UViewTarget::IsValid()
{
	return true;
}

FVector UViewTarget::GetViewLocation()
{
	return FVector::ZeroVector;
}

FRotator UViewTarget::GetViewRotation()
{
	return FRotator::ZeroRotator;
}

double UViewTarget::GetViewDistance()
{
	return 0;
}
