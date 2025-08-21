// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Components/Widget.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "UIFunctionLibrary.generated.h"

class UScreens;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UUIFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
	static bool IsWidgetOfType(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<UCommonActivatableWidget> WidgetClass);

	UFUNCTION(BlueprintCallable)
	static void PopWidget(UCommonActivatableWidgetContainerBase* Container);

	UFUNCTION(BlueprintCallable)
	static void ExtractWidgets(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<UCommonActivatableWidget> WidgetClass);

	template <typename T>
	static T* FloatWidget(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<T> WidgetClass)
	{
		return Cast<T>(FloatWidget(Container, WidgetClass));
	}

	UFUNCTION(BlueprintPure)
	static UCommonActivatableWidget* FloatWidget(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<UCommonActivatableWidget> WidgetClass);

	template <typename T>
	static T* ReplaceWidget(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<T> WidgetClass)
	{
		return Cast<T>(ReplaceWidget(Container, WidgetClass));
	}

	UFUNCTION(BlueprintPure)
	static UCommonActivatableWidget* ReplaceWidget(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<UCommonActivatableWidget> WidgetClass);

	template <class T>
	static T* GetParentWidget(const UWidget* InWidget)
	{
		return Cast<T>(GetParentWidget(InWidget));
	}
	
	UFUNCTION(BlueprintPure)
	static UWidget* GetParentWidget(const UWidget* InWidget);
	
	template <class T>
	static T* GetParentWidgetOfClass(const UWidget* InWidget)
	{
		return Cast<T>(GetParentWidgetOfClass(InWidget, T::StaticClass()));
	}

	UFUNCTION(BlueprintPure)
	static UWidget* GetParentWidgetOfClass(const UWidget* InWidget, const TSubclassOf<UWidget> InClass);

	template <class T>
	static T* GetTreeParentWidget(const UWidget* InWidget)
	{
		return Cast<T>(GetTreeParentWidget(InWidget));
	}

	UFUNCTION(BlueprintPure)
	static UUserWidget* GetTreeParentWidget(const UWidget* InWidget);
	
};
