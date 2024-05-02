// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/StructureAbilityProxy.h"
#include "GameplayAbilitySpecHandle.h"

FGameplayAbilitySpecHandle UStructureAbilityProxy::GetAbilityHandle()
{
	return FGameplayAbilitySpecHandle();
}

float UStructureAbilityProxy::GetArcLength()
{
	return 1;
}
