// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StructureTickLevel.h"
#include "HasTargetGroup.h"
#include "GameFramework/Pawn.h"
#include "Structure.generated.h"

class UStructureInventory;
class UItem;
class UStructureLocation;
class UStructureLayout;
class UStructureGameplay;
enum class EStructureValidationResult : uint8;
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
struct FStructureDamage;
struct FActiveGameplayEffectHandle;
struct FGameplayAbilitySpecHandle;

DECLARE_MULTICAST_DELEGATE_OneParam(FStructureIndicationChanged, UStructureIndication*)

UCLASS()
class DARKFRONTIER_API AStructure : public APawn, public IHasTargetGroup, public IAbilitySystemInterface
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

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TObjectPtr<UTargetGroup> HullTargetGroup;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TObjectPtr<UTargetGroup> ShieldTargetGroup;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UStructureLayout> Layout;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UStructureLocation> Location;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<ASector> InitialSector;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Sector")
	EStructureTickLevel TickLevel = EStructureTickLevel::Omitted;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced, Category="Inventory")
	TObjectPtr<UStructureInventory> Inventory;

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

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Input")
	FVector MoveInput = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Input")
	FVector RotateInput = FVector::ZeroVector;

public:

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
	UStructureLayout* GetLayout() const;

	UFUNCTION(BlueprintCallable)
	UStructureLocation* GetLocation() const;

	UFUNCTION(BlueprintCallable, Category="Sector")
	EStructureTickLevel GetTickLevel();

	UFUNCTION(BlueprintCallable, Category="Sector")
	bool SetTickLevel(EStructureTickLevel InLevel);

	UFUNCTION(BlueprintCallable, Category="Sector")
	void UpdateTickLevel();

	UFUNCTION(BlueprintCallable, Category="Inventory")
	UStructureInventory* GetInventory() const;

	UFUNCTION(BlueprintCallable, Category="Combat")
	AFaction* GetOwningFaction() const;

	UFUNCTION(BlueprintCallable, Category="Combat")
	void SetOwningFaction(AFaction* InFaction);

	UFUNCTION(BlueprintCallable, Category="Combat")
	AStructure* GetTarget() const;

	UFUNCTION(BlueprintCallable, Category="Combat")
	void SetTarget(AStructure* InTarget);

	UFUNCTION(BlueprintCallable, Category="Combat")
	bool IsPlayer() const;

	UFUNCTION(BlueprintCallable, Category="Combat")
	bool IsSelected() const;

	UFUNCTION(BlueprintCallable)
	UStructureGameplay* GetGameplay() const;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UTargetGroup* GetTargetGroup() const override;

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
