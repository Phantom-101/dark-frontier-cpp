// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sectors/SectorLocation.h"
#include "Structures/Targetable.h"
#include "ItemPod.generated.h"

class UTargetable;
class USectorLocation;
class UItemPodSelector;
class UInventory;
class UItem;

UCLASS(Abstract)
class DARKFRONTIER_API AItemPod : public AActor, public ISectorLocationInterface, public ITargetableInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UItem> Item;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int Quantity;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<USectorLocation> Location;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UTargetable> Targetable;

public:

	AItemPod();

	void Init(UItem* InItem, int InQuantity);

protected:

	virtual void Tick(float DeltaSeconds) override;

public:

	UItem* GetItem() const;

	int GetQuantity() const;

	void AddToInventory(UInventory* Inventory);

	UStaticMeshComponent* GetStaticMesh() const;

	COMPONENT_ACCESSOR_NAME(SectorLocation, Location);
	COMPONENT_ACCESSOR(Targetable);

};
