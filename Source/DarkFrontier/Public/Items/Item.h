// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObject.h"
#include "Engine/DataAsset.h"
#include "Item.generated.h"

class UItemObject;
/**
 * 
 */
UCLASS(BlueprintType)
class DARKFRONTIER_API UItem : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UTexture2D> Icon;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText Description;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Volume = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Mass = 0;

	UItemObject* ToObject();
	
};

inline UItemObject* UItem::ToObject()
{
	UItemObject* Obj = NewObject<UItemObject>();
	Obj->Item = this;
	return Obj;
}
