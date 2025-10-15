// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ItemList.h"
#include "UObject/Object.h"
#include "ItemHandle.generated.h"

class UItemList;
class UItem;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UItemHandle : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UItemList> List;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UItem> Item;

	static UItemHandle* New(UItemList* List, UItem* Item);

	bool IsValid() const;

	UFUNCTION(BlueprintPure)
	int GetQuantity() const;
	
};

inline UItemHandle* UItemHandle::New(UItemList* List, UItem* Item)
{
	UItemHandle* Object = NewObject<UItemHandle>();
	Object->List = List;
	Object->Item = Item;
	return Object;
}

inline bool UItemHandle::IsValid() const
{
	return ::IsValid(List) && ::IsValid(Item);
}

inline int UItemHandle::GetQuantity() const
{
	return List->GetQuantity(Item);
}
