// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objects/Targetable.h"
#include "ItemPod.generated.h"

class UItemPodSelector;
class ASector;
class UInventory;
class UItem;

UCLASS(Abstract)
class DARKFRONTIER_API AItemPod : public AActor, public ITargetable
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UItem> Item;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int Quantity;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<ASector> Sector;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UItemPodSelector> SelectorClass;

public:

	AItemPod();

	void Init(UItem* InItem, int InQuantity);

protected:

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	UItem* GetItem() const;

	int GetQuantity() const;

	void AddToInventory(UInventory* Inventory);

	UStaticMeshComponent* GetStaticMesh() const;

	virtual bool IsTargetable(AStructure* Structure) const override;

	virtual TSubclassOf<USelector> GetSelectorClass() const override;
	
};
