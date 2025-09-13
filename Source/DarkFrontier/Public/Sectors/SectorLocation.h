// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SectorLocation.generated.h"

class ASector;

DECLARE_MULTICAST_DELEGATE_OneParam(FSectorChanged, ASector*)

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DARKFRONTIER_API USectorLocation : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<ASector> Sector;

public:

	// Listen to this event for type specific handling
	// Such as structures propagating sector changes to dockers
	FSectorChanged OnSectorChanged;

	UFUNCTION(BlueprintCallable)
	ASector* GetSector() const;
	
	UFUNCTION(BlueprintCallable)
	void SetSector(ASector* InSector);

	UFUNCTION(BlueprintCallable)
	void UpdateSector();

	UFUNCTION(BlueprintCallable)
	FVector GetLocation() const;

};
