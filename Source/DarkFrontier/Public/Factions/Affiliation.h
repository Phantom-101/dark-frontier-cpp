// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Affiliation.generated.h"

class AFaction;

DECLARE_MULTICAST_DELEGATE_OneParam(FFactionChanged, AFaction*)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DARKFRONTIER_API UAffiliation : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TObjectPtr<AFaction> Faction;

public:

	FFactionChanged OnFactionChanged;

protected:

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	UFUNCTION(BlueprintCallable)
	AFaction* GetFaction() const;
	
	UFUNCTION(BlueprintCallable)
	void SetFaction(AFaction* InFaction);

};

UINTERFACE()
class UAffiliationInterface : public UInterface
{
	GENERATED_BODY()
};

class IAffiliationInterface
{
	GENERATED_BODY()

public:

	virtual UAffiliation* GetAffiliation() const = 0;

};
