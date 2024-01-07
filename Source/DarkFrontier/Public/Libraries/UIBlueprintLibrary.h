// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PanelWidget.h"
#include "Components/Widget.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UIBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UUIBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	template<class T>
	static T* GetParentWidgetOfClass(UWidget* InWidget)
	{
		if(const UObject* Top = InWidget->GetParent())
		{
			while(true)
			{
				UObject* CurrentOuter = Top->GetOuter();
				if(CurrentOuter->IsA(T::StaticClass()))
				{
					return Cast<T>(CurrentOuter);
				}
				if(CurrentOuter == nullptr)
				{
					return nullptr;
				}
				Top = CurrentOuter;
			}
		}
		return nullptr;
	}

	static UWidget* GetParentWidgetOfClass(const TSubclassOf<UWidget> InClass, const UWidget* InWidget)
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
				if(CurrentOuter == nullptr)
				{
					return nullptr;
				}
				Top = CurrentOuter;
			}
		}
		return nullptr;
	}
	
};
