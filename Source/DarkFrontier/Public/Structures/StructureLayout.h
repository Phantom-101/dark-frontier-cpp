// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureFacility.h"
#include "UObject/Object.h"
#include "StructureLayout.generated.h"

struct FStructureLayoutData;
class UStructureSlot;
class UStructureFacility;
class AStructurePart;
class AStructure;

DECLARE_MULTICAST_DELEGATE(FStructureLayoutChanged)

/**
 * 
 */
UCLASS(DefaultToInstanced)
class DARKFRONTIER_API UStructureLayout : public UObject
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

	FStructureLayoutChanged OnUpdated;

	static UStructureLayout* CreateLayout(AStructure* Structure);

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
	void RemoveAll();

	UFUNCTION(BlueprintCallable)
	void ConnectAll();

	UFUNCTION(BlueprintCallable)
	TArray<AStructurePart*> GetConnected() const;

	UFUNCTION(BlueprintCallable)
	TArray<AStructurePart*> GetDisconnected() const;
	
	UFUNCTION(BlueprintCallable)
	void RemoveUnconnected();

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

	UFUNCTION(BlueprintCallable)
	bool IsValid();

	UFUNCTION(BlueprintCallable)
	bool LoadData(FStructureLayoutData Data);
	
private:

	void UpdateLayout();

};
