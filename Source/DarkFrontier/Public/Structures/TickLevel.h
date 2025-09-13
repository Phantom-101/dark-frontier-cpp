// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Macros.h"
#include "Components/ActorComponent.h"
#include "TickLevel.generated.h"

class ASector;
class USectorLocation;

UENUM(BlueprintType)
enum class ETickLevel : uint8
{
	None,
	Partial,
	Full
};

DECLARE_MULTICAST_DELEGATE_OneParam(FTickLevelChanged, ETickLevel)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DARKFRONTIER_API UTickLevel : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	ETickLevel TickLevel = ETickLevel::None;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<USectorLocation> SectorLocation;

public:

	FTickLevelChanged OnTickLevelChanged;

	UTickLevel();

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	ETickLevel GetTickLevel() const;

private:

	void UpdateTickLevel(ASector* Sector);

};

UINTERFACE()
class UTickLevelInterface : public UInterface
{
	GENERATED_BODY()
};

class ITickLevelInterface
{
	GENERATED_BODY()

public:

	virtual UTickLevel* GetTickLevel() const = 0;

};
