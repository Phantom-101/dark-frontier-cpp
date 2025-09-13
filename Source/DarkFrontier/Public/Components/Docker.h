// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Docker.generated.h"

class UStructureDock;

DECLARE_MULTICAST_DELEGATE_OneParam(FDockChanged, UStructureDock*)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DARKFRONTIER_API UDocker : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UStructureDock> Dock;

public:

	FDockChanged OnDockChanged;

	UFUNCTION(BlueprintCallable)
	UStructureDock* GetDock() const;

	UFUNCTION(BlueprintCallable)
	bool EnterDock(UStructureDock* Target);

	UFUNCTION(BlueprintCallable)
	bool ExitDock();

};
