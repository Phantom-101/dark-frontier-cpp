// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/UniverseGameMode.h"
#include "Game/TradeParameters.h"

AUniverseGameMode::AUniverseGameMode()
{
	TradeParameters = CreateDefaultSubobject<UTradeParameters>("TradeParameters");
}

TArray<UItem*> AUniverseGameMode::GetItemList()
{
	return ItemList;
}

const UTradeParameters* AUniverseGameMode::GetTradeParameters()
{
	return TradeParameters;
}
