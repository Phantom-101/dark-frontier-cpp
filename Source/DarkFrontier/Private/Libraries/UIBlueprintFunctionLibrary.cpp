// Fill out your copyright notice in the Description page of Project Settings.

#include "Libraries/UIBlueprintFunctionLibrary.h"

UWidget* UUIBlueprintFunctionLibrary::GetParentWidgetOfClass(const TSubclassOf<UWidget> InClass, const UWidget* InWidget)
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

		if(Parent != nullptr && Parent->IsA(InClass))
		{
			return Parent;
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
