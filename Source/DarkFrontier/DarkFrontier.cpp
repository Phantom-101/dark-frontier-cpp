// Fill out your copyright notice in the Description page of Project Settings.

#include "DarkFrontier.h"
#include "Modules/ModuleManager.h"
#include "Log.h"

void FDarkFrontier::StartupModule()
{
	UE_LOG(LogDarkFrontier, Log, TEXT("DarkFrontier module starting up"));
}

void FDarkFrontier::ShutdownModule()
{
	UE_LOG(LogDarkFrontier, Log, TEXT("DarkFrontier module shutting down"));
}

IMPLEMENT_PRIMARY_GAME_MODULE(FDarkFrontier, DarkFrontier, "DarkFrontier");
