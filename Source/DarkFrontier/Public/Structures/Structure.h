// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StructureTickLevel.h"
#include "GameFramework/Pawn.h"
#include "Structure.generated.h"

class UStructureIndices;
class UStructureGameplay;
enum class EStructureValidationResult : uint8;
class UInventory;
class UStructureAbilitySystemComponent;
class UStructureAttributeSet;
class USpringArmComponent;
class UCameraComponent;
class UGameplayEffect;
class AStructurePart;
class AFaction;
class UStructureIndication;
class ASector;
class UStructureDock;
class UHullIndication;
class UDistanceIndication;
class USpeedIndication;
struct FStructureDamage;
struct FActiveGameplayEffectHandle;
struct FGameplayAbilitySpecHandle;

DECLARE_MULTICAST_DELEGATE(FStructureStateChanged)
DECLARE_MULTICAST_DELEGATE_OneParam(FStructureIndicationChanged, UStructureIndication*)

UCLASS()
class DARKFRONTIER_API AStructure : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AStructure();

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UStructureIndices> Indices;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Docking")
	TObjectPtr<UStructureDock> CurrentDock;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Sector")
	EStructureTickLevel TickLevel = EStructureTickLevel::Omitted;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Sector")
	TObjectPtr<ASector> CurrentSector;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced, Category="Inventory")
	TObjectPtr<UInventory> Inventory;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Combat")
	TObjectPtr<AFaction> OwningFaction;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Combat")
	TObjectPtr<AStructure> Target;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UStructureGameplay> Gameplay;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	FGameplayTag HullDamageCueTag;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	FGameplayTag ShieldDamageCueTag;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Gameplay")
	TArray<TObjectPtr<UStructureIndication>> Indications;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TSubclassOf<UHullIndication> HullIndicationClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TSubclassOf<UDistanceIndication> DistanceIndicationClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TSubclassOf<USpeedIndication> SpeedIndicationClass;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Input")
	FVector MoveInput = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Input")
	FVector RotateInput = FVector::ZeroVector;

public:

	FStructureStateChanged OnLayoutChanged;

	FStructureIndicationChanged OnIndicationAdded;

	FStructureIndicationChanged OnIndicationRemoved;

protected:

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
public:

	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintCallable, Category="Lifetime")
	bool TryDestroy();

	UFUNCTION(BlueprintCallable)
	UStructureIndices* GetIndices() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	EStructureValidationResult ValidateLayout();

	UFUNCTION(BlueprintCallable, Category="Layout")
	bool LoadLayout(struct FStructureLayout InLayout);

	UFUNCTION(BlueprintCallable, Category="Layout")
	void UpdateLayoutInformation();

	UFUNCTION(BlueprintCallable, Category="Docking")
	UStructureDock* GetDock() const;

	UFUNCTION(BlueprintCallable, Category="Docking")
	bool TryDock(UStructureDock* InDock);

	UFUNCTION(BlueprintCallable, Category="Docking")
	bool TryUnDock();
	
	UFUNCTION(BlueprintCallable, Category="Sector")
	EStructureTickLevel GetTickLevel();

	UFUNCTION(BlueprintCallable, Category="Sector")
	bool SetTickLevel(EStructureTickLevel InLevel);

	UFUNCTION(BlueprintCallable, Category="Sector")
	void UpdateTickLevel();

	UFUNCTION(BlueprintCallable, Category="Sector")
	bool TryEnterSector(ASector* InSector);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	UInventory* GetInventory() const;

	UFUNCTION(BlueprintCallable, Category="Combat")
	AFaction* GetOwningFaction() const;

	UFUNCTION(BlueprintCallable, Category="Combat")
	void SetOwningFaction(AFaction* InFaction);

	UFUNCTION(BlueprintCallable, Category="Combat")
	AStructure* GetTarget() const;

	UFUNCTION(BlueprintCallable, Category="Combat")
	void SetTarget(AStructure* InTarget);

	UFUNCTION(BlueprintCallable)
	UStructureGameplay* GetGameplay() const;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	TArray<UStructureIndication*> GetIndications();

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	UStructureIndication* AddIndication(TSubclassOf<UStructureIndication> IndicationClass);

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void RemoveIndication(UStructureIndication* Indication);

	UFUNCTION(BlueprintCallable, Category="Input")
	void SetMoveInput(FVector InInput);

	UFUNCTION(BlueprintCallable, Category="Input")
	void SetRotateInput(FVector InInput);
	
	UFUNCTION(BlueprintCallable, Category="Camera")
	USpringArmComponent* GetCameraSpringArm() const;

protected:
	
	FVector CalculateImpulse(const FVector& RawVelocities, const FVector& RawInput, float MaxSpeed, float Accel, float DeltaTime) const;

	UFUNCTION()
	void HandlePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, const FVector HitLocation, UPrimitiveComponent* HitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser);
	
};
