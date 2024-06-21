// Fill out your copyright notice in the Description page of Project Settings.

#include "Libraries/UIBlueprintFunctionLibrary.h"

UWidget* UUIBlueprintFunctionLibrary::GetParentWidgetOfClass(const TSubclassOf<UWidget> InClass, const UWidget* InWidget)
{
	if(const UObject* Top = InWidget->GetParent())
	{
		while(true)
		{
			UObject* CurrentOuter = Top->GetOuter();
			if(CurrentOuter->IsA(InClass))
			{
				return Cast<UWidget>(CurrentOuter);
			}
			if(!CurrentOuter)
			{
				return nullptr;
			}
			Top = CurrentOuter;
		}
	}
	return nullptr;
}
