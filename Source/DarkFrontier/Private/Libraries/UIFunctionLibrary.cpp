// Fill out your copyright notice in the Description page of Project Settings.

#include "Libraries/UIFunctionLibrary.h"
#include "Blueprint/IUserListEntry.h"
#include "Components/ListViewBase.h"

bool UUIFunctionLibrary::IsWidgetOfType(const UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<UCommonActivatableWidget>& WidgetClass)
{
	const UCommonActivatableWidget* Widget = Container->GetActiveWidget();
	return IsValid(Widget) && Widget->IsA(WidgetClass);
}

void UUIFunctionLibrary::PopWidget(UCommonActivatableWidgetContainerBase* Container)
{
	UCommonActivatableWidget* Widget = Container->GetActiveWidget();
	if(Widget != nullptr)
	{
		Container->RemoveWidget(*Widget);
	}
}

void UUIFunctionLibrary::ExtractWidgets(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	for(UCommonActivatableWidget* Widget : TArray(Container->GetWidgetList()))
	{
		if(Widget->IsA(WidgetClass))
		{
			Container->RemoveWidget(*Widget);
		}
	}
}

UCommonActivatableWidget* UUIFunctionLibrary::FloatWidget(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	if(IsWidgetOfType(Container, WidgetClass))
	{
		return Container->GetActiveWidget();
	}
	ExtractWidgets(Container, WidgetClass);
	return Container->AddWidget(WidgetClass);
}

UCommonActivatableWidget* UUIFunctionLibrary::ReplaceWidget(UCommonActivatableWidgetContainerBase* Container, const TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	PopWidget(Container);
	return Container->AddWidget(WidgetClass);
}

UWidget* UUIFunctionLibrary::GetParentWidget(const UWidget* InWidget)
{
	if(UWidget* Parent = InWidget->GetParent(); Parent != nullptr)
	{
		return Parent;
	}

	// List item entries will have null parent
	if(InWidget->Implements<UUserListEntry>())
	{
		return Cast<IUserListEntry>(InWidget)->GetOwningListView();
	}

	// No way to get the container of an activatable widget for now
	
	// Parent is null when currently on the top-most widget in a user widget tree
	// Call GetOuter twice to get the widget tree and then the wrapping widget
	UUserWidget* Parent = GetTreeParentWidget(InWidget);
	if(Parent != nullptr)
	{
		return Parent;
	}

	// If on a widget added directly to the viewport, outer will be a GameInstance
	
	return nullptr;
}

UWidget* UUIFunctionLibrary::GetParentWidgetOfClass(const UWidget* InWidget, const TSubclassOf<UWidget> InClass)
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

UUserWidget* UUIFunctionLibrary::GetTreeParentWidget(const UWidget* InWidget)
{
	const UWidgetTree* Tree = Cast<UWidgetTree>(InWidget->GetOuter());
	if(Tree != nullptr)
	{
		return Cast<UUserWidget>(Tree->GetOuter());
	}

	return nullptr;
}
