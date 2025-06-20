// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Styling/AlternateColor.h"
#include "Libraries/UIBlueprintFunctionLibrary.h"

void UAlternateColor::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(Colors.Num() == 0)
	{
		return;
	}
	
	const UAlternateColor* Current = this;
	int Depth = -1;
	while(Current != nullptr)
	{
		Depth++;
		Current = UUIBlueprintFunctionLibrary::GetParentWidgetOfClass<UAlternateColor>(Current);
	}

	SetForegroundColor(Colors[Depth % Colors.Num()]);
}
