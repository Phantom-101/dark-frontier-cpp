// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FDarkFrontier : public IModuleInterface
{

public:

	static FDarkFrontier& Get()
	{
		return FModuleManager::LoadModuleChecked<FDarkFrontier>("DarkFrontier");
	}

	static bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("DarkFrontier");
	}

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
};