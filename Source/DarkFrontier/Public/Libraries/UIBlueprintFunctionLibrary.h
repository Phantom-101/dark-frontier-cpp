// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Components/Widget.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "UIBlueprintFunctionLibrary.generated.h"

class UUIBase;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UUIBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	template <typename T>
	static T* PopWidget(UCommonActivatableWidgetContainerBase* Container)
	{
		UCommonActivatableWidget* Widget = Container->GetActiveWidget();
		if(Widget != nullptr)
		{
			Container->RemoveWidget(*Widget);
			return Cast<T>(Widget);
		}
		return nullptr;
	}

	UFUNCTION(BlueprintCallable)
	static UCommonActivatableWidget* PopWidget(UCommonActivatableWidgetContainerBase* Container);

	template <typename T>
	static T* ExtractWidget(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<T> WidgetClass)
	{
		TArray Widgets(Container->GetWidgetList());
		Algo::Reverse(Widgets);
		for(UCommonActivatableWidget* Widget : Widgets)
		{
			if(Widget->IsA(WidgetClass))
			{
				Container->RemoveWidget(*Widget);
				return Cast<T>(Widget);
			}
		}
		return nullptr;
	}

	UFUNCTION(BlueprintCallable)
	static UCommonActivatableWidget* ExtractWidget(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<UCommonActivatableWidget> WidgetClass);

	template <typename T>
	static T* FloatWidget(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<T> WidgetClass)
	{
		T* Widget = ExtractWidget<T>(Container, WidgetClass);
		if(Widget != nullptr)
		{
			Container->AddWidgetInstance(*Widget);
			return Widget;
		}
		return Container->AddWidget<T>(WidgetClass);
	}

	UFUNCTION(BlueprintCallable)
	static UCommonActivatableWidget* FloatWidget(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<UCommonActivatableWidget> WidgetClass);

	template <typename T>
	static T* ReplaceWidget(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<T> WidgetClass)
	{
		PopWidget(Container);
		return Container->AddWidget<T>(WidgetClass);
	}

	UFUNCTION(BlueprintCallable)
	static UCommonActivatableWidget* ReplaceWidget(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<UCommonActivatableWidget> WidgetClass);

	template <class T>
	static T* GetParentWidget(const UWidget* InWidget)
	{
		UWidget* Parent = InWidget->GetParent();
		if(Parent != nullptr)
		{
			return Cast<T>(Parent);
		}
	
		// Parent is null when currently on the top-most widget in a user widget tree
		// Call GetOuter twice to get the widget tree and then the wrapping user widget
		// Which may be in the widget tree of another user widget
		// If on a widget added directly to the viewport, outer will be a GameInstance
		// If on an entry widget, need to call GetOwningListView or equivalent
		// If on an activatable widget, GetOuter seems to skip directly to the enclosing user widget
		const UWidgetTree* Tree = Cast<UWidgetTree>(InWidget->GetOuter());
		if(Tree != nullptr)
		{
			return Cast<T>(Tree->GetOuter());
		}

		return nullptr;
	}
	
	UFUNCTION(BlueprintCallable)
	static UWidget* GetParentWidget(const UWidget* InWidget);
	
	template <class T>
	static T* GetParentWidgetOfClass(const UWidget* InWidget)
	{
		UWidget* Current = GetParentWidget(InWidget);
		while(Current != nullptr)
		{
			if(Current->IsA(T::StaticClass()))
			{
				return Cast<T>(Current);
			}
			Current = GetParentWidget(Current);
		}
		return nullptr;
	}

	UFUNCTION(BlueprintCallable)
	static UWidget* GetParentWidgetOfClass(const TSubclassOf<UWidget> InClass, const UWidget* InWidget);
	
};
