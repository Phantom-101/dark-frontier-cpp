// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "ItemObject.h"
#include "Engine/DataAsset.h"
#include "Item.generated.h"

struct FItemFragment;
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

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Value = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(BaseStruct="/Script/DarkFrontier.ItemFragment", ExcludeBaseStruct))
	TArray<TInstancedStruct<FItemFragment>> Fragments;

	const TArray<TInstancedStruct<FItemFragment>>& GetFragments() const;

	UItemObject* ToObject();
	
};

// TODO move to cpp file
inline const TArray<TInstancedStruct<FItemFragment>>& UItem::GetFragments() const
{
	return Fragments;
}

inline UItemObject* UItem::ToObject()
{
	UItemObject* Obj = NewObject<UItemObject>();
	Obj->Item = this;
	return Obj;
}
