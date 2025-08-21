// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemPod.generated.h"

class UInventory;
class UItem;

UCLASS(Abstract)
class DARKFRONTIER_API AItemPod : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UItem> Item;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int Quantity;

public:

	AItemPod();

	void Init(UItem* InItem, int InQuantity);

protected:

	virtual void BeginPlay() override;

public:

	UItem* GetItem() const;

	int GetQuantity() const;

	void AddToInventory(UInventory* Inventory);

	UStaticMeshComponent* GetStaticMesh() const;
	
};
