// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/AlternatingColorScope.h"
#include "Blueprint/WidgetTree.h"
#include "Slate/SObjectWidget.h"

void UAlternatingColorScope::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(Colors.Num() == 0)
	{
		return;
	}

	SWidget* Current = MyWidget.Pin().Get();
	int Depth = -1;
	while(Current != nullptr)
	{
		FString Type = Current->GetTypeAsString();
		if(Type == "SObjectWidget")
		{
			if(static_cast<SObjectWidget*>(Current)->GetWidgetObject()->IsA<UAlternatingColorScope>())
			{
				Depth++;
			}
		}
		else if (Type == "SConstraintCanvas")
		{
			break;
		}
		
		Current = Current->GetParentWidget().Get();
	}

	SetForegroundColor(Colors[Depth % Colors.Num()]);
}
