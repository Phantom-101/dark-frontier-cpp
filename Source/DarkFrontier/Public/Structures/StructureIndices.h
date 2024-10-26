// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureFacility.h"
#include "UObject/Object.h"
#include "StructureIndices.generated.h"

class AStructureSubactor;
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
	bool AddPart(AStructurePart* Part);

	UFUNCTION(BlueprintCallable)
	bool RemovePart(AStructurePart* Part);

	UFUNCTION(BlueprintCallable)
	void ReconnectParts();
	
	UFUNCTION(BlueprintCallable)
	void CullParts();

	UFUNCTION(BlueprintCallable)
	TArray<UStructureSlot*> GetSlots();

	UFUNCTION(BlueprintCallable)
	TArray<UStructureFacility*> GetFacilities();

	template<typename T>
	TArray<T*> GetFacilities()
	{
		TArray<T*> Ret;
		for(UStructureFacility* Facility : Facilities)
		{
			if(Facility->IsA<T>())
			{
				Ret.Add(Cast<T>(Facility));
			}
		}
		return Ret;
	}
	
private:

	void UpdateIndices();

};
