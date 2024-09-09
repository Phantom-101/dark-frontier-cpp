// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StructureIndices.generated.h"

class UStructureSlot;
class UStructureFacility;
class AStructurePart;
class AStructure;

DECLARE_MULTICAST_DELEGATE(FStructureIndicesUpdated)

/**
 * 
 */
UCLASS(DefaultToInstanced)
class DARKFRONTIER_API UStructureIndices : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<AStructurePart> RootPart;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TArray<TObjectPtr<AStructurePart>> Parts;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TArray<TObjectPtr<UStructureSlot>> Slots;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TArray<TObjectPtr<UStructureFacility>> Facilities;

public:

	FStructureIndicesUpdated OnUpdated;

	static UStructureIndices* CreateIndices(AStructure* Structure);

	UFUNCTION(BlueprintCallable)
	AStructure* GetStructure() const;

	UFUNCTION(BlueprintCallable)
	AStructurePart* GetRootPart() const;

	UFUNCTION(BlueprintCallable)
	TArray<AStructurePart*> GetParts();

	UFUNCTION(BlueprintCallable)
	AStructurePart* GetPart(FString Id);

	UFUNCTION(BlueprintCallable)
	TArray<UStructureSlot*> GetSlots();

	UFUNCTION(BlueprintCallable)
	TArray<UStructureFacility*> GetFacilities();

	UFUNCTION(BlueprintCallable)
	bool AddPart(AStructurePart* Part);

	UFUNCTION(BlueprintCallable)
	bool RemovePart(AStructurePart* Part);

private:

	void UpdateIndices();

};
