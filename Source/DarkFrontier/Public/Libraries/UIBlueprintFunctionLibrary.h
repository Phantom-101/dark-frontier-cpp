// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Components/Widget.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "UIBlueprintFunctionLibrary.generated.h"

class UScreens;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UUIBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
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

	UFUNCTION(BlueprintCallable)
	static UCommonActivatableWidget* FloatWidget(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<UCommonActivatableWidget> WidgetClass);

	template <typename T>
	static T* ReplaceWidget(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<T> WidgetClass)
	{
		return Cast<T>(ReplaceWidget(Container, WidgetClass));
	}

	UFUNCTION(BlueprintCallable)
	static UCommonActivatableWidget* ReplaceWidget(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<UCommonActivatableWidget> WidgetClass);

	template <class T>
	static T* GetParentWidget(const UWidget* InWidget)
	{
		return Cast<T>(GetParentWidget(InWidget));
	}
	
	UFUNCTION(BlueprintCallable)
	static UWidget* GetParentWidget(const UWidget* InWidget);
	
	template <class T>
	static T* GetParentWidgetOfClass(const UWidget* InWidget)
	{
		return Cast<T>(GetParentWidgetOfClass(InWidget, T::StaticClass()));
	}

	UFUNCTION(BlueprintCallable)
	static UWidget* GetParentWidgetOfClass(const UWidget* InWidget, const TSubclassOf<UWidget> InClass);
	
};
