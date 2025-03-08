// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StructureLocation.generated.h"

class UStructureDock;
class ASector;
class AStructure;

DECLARE_MULTICAST_DELEGATE_OneParam(FDockChanged, UStructureDock*)

/**
 * 
 */
UCLASS(DefaultToInstanced)
class DARKFRONTIER_API UStructureLocation : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<ASector> Sector;
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<AStructure> DockStructure;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UStructureDock> Dock;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TArray<TObjectPtr<AStructure>> Dockers;

public:

	FDockChanged OnDockChanged;

	static UStructureLocation* CreateLocation(AStructure* Structure);

	UFUNCTION(BlueprintCallable)
	AStructure* GetStructure() const;

	UFUNCTION(BlueprintCallable)
	ASector* GetSector() const;

	UFUNCTION(BlueprintCallable)
	bool EnterSector(ASector* Target);

	UFUNCTION(BlueprintCallable)
	bool ExitSector();

	UFUNCTION(BlueprintCallable)
	AStructure* GetDockStructure() const;
	
	UFUNCTION(BlueprintCallable)
	UStructureDock* GetDock() const;

	UFUNCTION(BlueprintCallable)
	bool EnterDock(UStructureDock* Target);

	UFUNCTION(BlueprintCallable)
	bool ExitDock();
	
	UFUNCTION(BlueprintCallable)
	TArray<AStructure*> GetDockers() const;

	UFUNCTION(BlueprintCallable)
	TArray<AStructure*> GetInSubTree() const;

	UFUNCTION(BlueprintCallable)
	TArray<AStructure*> GetInTree() const;
	
};
