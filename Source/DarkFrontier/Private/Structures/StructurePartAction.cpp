// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructurePartAction.h"

void UStructurePartAction::Trigger() const
{
	if(OnTriggered.IsBound())
	{
		OnTriggered.Execute();
	}
}
