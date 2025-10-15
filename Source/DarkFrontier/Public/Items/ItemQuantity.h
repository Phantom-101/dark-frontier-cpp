// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemQuantity.generated.h"

class UItem;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UItemQuantity : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UItem> Item;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Quantity;

	static UItemQuantity* New(UItem* Item, int Quantity);
	
};

inline UItemQuantity* UItemQuantity::New(UItem* Item, const int Quantity)
{
	UItemQuantity* Object = NewObject<UItemQuantity>();
	Object->Item = Item;
	Object->Quantity = Quantity;
	return Object;
}
