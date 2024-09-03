// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Log.h"
#include "Blueprint/WidgetTree.h"
#include "Components/PanelWidget.h"
#include "Components/Widget.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UIBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UUIBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	template <class T>
	static T* GetParentWidgetOfClass(const UWidget* InWidget)
	{
		const UWidget* Current = InWidget;
		while(Current != nullptr)
		{
			UWidget* Parent = Current->GetParent();
			if(Parent == nullptr)
			{
				// Parent is null when currently on the top-most widget in a user widget tree
				// Call get outer twice to get tree then wrapping user widget
				const UWidgetTree* Tree = Cast<UWidgetTree>(Current->GetOuter());
				Parent = Cast<UWidget>(Tree->GetOuter());
			}

			if(Parent != nullptr && Parent->IsA(T::StaticClass()))
			{
				return Cast<T>(Parent);
			}
				
			if(Current == Parent)
			{
				UE_LOG(LogDarkFrontier, Warning, TEXT("Reference cycle detected when finding parent widget of type"))
				return nullptr;
			}

			Current = Parent;
		}
		
		return nullptr;
	}

	UFUNCTION(BlueprintCallable)
	static UWidget* GetParentWidgetOfClass(const TSubclassOf<UWidget> InClass, const UWidget* InWidget);
	
};
