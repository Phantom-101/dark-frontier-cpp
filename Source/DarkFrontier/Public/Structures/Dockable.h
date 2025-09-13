// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Macros.h"
#include "Components/ActorComponent.h"
#include "Dockable.generated.h"

class ASector;
class AStructure;
class UStructureDock;

DECLARE_MULTICAST_DELEGATE_OneParam(FDockChanged, UStructureDock*)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DARKFRONTIER_API UDockable : public UActorComponent
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UStructureDock> Dock;

public:

	FDockChanged OnDockChanged;

	UFUNCTION(BlueprintCallable)
	AStructure* GetStructure() const;

	UFUNCTION(BlueprintCallable)
	UStructureDock* GetDock() const;

	UFUNCTION(BlueprintCallable)
	AStructure* GetDockStructure() const;

	UFUNCTION(BlueprintCallable)
	bool EnterDock(UStructureDock* Target);

	UFUNCTION(BlueprintCallable)
	bool ExitDock();

private:

	void PropagateSector(ASector* Sector) const;

};

UINTERFACE()
class UDockableInterface : public UInterface
{
	GENERATED_BODY()
};

class IDockableInterface
{
	GENERATED_BODY()

public:

	virtual UDockable* GetDockable() const = 0;

};
