// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Info/Factory/InfoFactoryEntry.h"
#include "CommonTextBlock.h"
#include "Macros.h"
#include "Components/ListView.h"
#include "Items/ItemQuantity.h"
#include "Items/Recipe.h"
#include "Libraries/ItemFunctionLibrary.h"
#include "Structures/StructureProduction.h"

void UInfoFactoryEntry::Init(UStructureProduction* InProduction)
{
	Production = InProduction;
	GUARD(IsValid(Production));

	const URecipe* Recipe = Production->GetRecipe();
	GUARD(IsValid(Recipe));

	Inputs->SetListItems<UItemQuantity*>(UItemFunctionLibrary::ToQuantities(Recipe->Inputs));
	Outputs->SetListItems<UItemQuantity*>(UItemFunctionLibrary::ToQuantities(Recipe->Outputs));
}

void UInfoFactoryEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);
	Init(Cast<UStructureProduction>(ListItemObject));
}

void UInfoFactoryEntry::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	GUARD(IsValid(Production));

	const URecipe* Recipe = Production->GetRecipe();
	GUARD(IsValid(Recipe));
	
	TimeText->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Recipe->Time - Production->GetProgress()))));
}
