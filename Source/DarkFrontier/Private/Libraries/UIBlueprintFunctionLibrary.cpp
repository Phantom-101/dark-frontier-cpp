// Fill out your copyright notice in the Description page of Project Settings.

#include "Libraries/UIBlueprintFunctionLibrary.h"

bool UUIBlueprintFunctionLibrary::IsWidgetOfType(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	return Container->GetActiveWidget()->IsA(WidgetClass);
}

void UUIBlueprintFunctionLibrary::PopWidget(UCommonActivatableWidgetContainerBase* Container)
{
	UCommonActivatableWidget* Widget = Container->GetActiveWidget();
	if(Widget != nullptr)
	{
		Container->RemoveWidget(*Widget);
	}
}

void UUIBlueprintFunctionLibrary::ExtractWidgets(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	for(UCommonActivatableWidget* Widget : TArray(Container->GetWidgetList()))
	{
		if(Widget->IsA(WidgetClass))
		{
			Container->RemoveWidget(*Widget);
		}
	}
}

UCommonActivatableWidget* UUIBlueprintFunctionLibrary::FloatWidget(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	if(IsWidgetOfType(Container, WidgetClass))
	{
		return Container->GetActiveWidget();
	}
	ExtractWidgets(Container, WidgetClass);
	return Container->AddWidget(WidgetClass);
}

UCommonActivatableWidget* UUIBlueprintFunctionLibrary::ReplaceWidget(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	PopWidget(Container);
	return Container->AddWidget(WidgetClass);
}

UWidget* UUIBlueprintFunctionLibrary::GetParentWidget(const UWidget* InWidget)
{
	UWidget* Parent = InWidget->GetParent();
	if(Parent != nullptr)
	{
		return Parent;
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
		return Cast<UWidget>(Tree->GetOuter());
	}

	return nullptr;
}

UWidget* UUIBlueprintFunctionLibrary::GetParentWidgetOfClass(const TSubclassOf<UWidget> InClass, const UWidget* InWidget)
{
	UWidget* Current = GetParentWidget(InWidget);
	while(Current != nullptr)
	{
		if(Current->IsA(InClass))
		{
			return Current;
		}
		Current = GetParentWidget(Current);
	}
	return nullptr;
}
