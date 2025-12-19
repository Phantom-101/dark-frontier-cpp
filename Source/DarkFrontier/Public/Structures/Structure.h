// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "Dockable.h"
#include "GameplayTagContainer.h"
#include "Targetable.h"
#include "Factions/Affiliation.h"
#include "GameFramework/Pawn.h"
#include "Sectors/SectorLocation.h"
#include "Structure.generated.h"

class UTargetable;
class USectorLocation;
class UStructureInventory;
class UItem;
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
class DARKFRONTIER_API AStructure : public APawn, public ISectorLocationInterface,
	public IAffiliationInterface, public IDockableInterface, public ITargetableInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UStructureLayout> Layout;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<USectorLocation> Location;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UAffiliation> Affiliation;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UDockable> Dockable;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UTargetable> Targetable;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced, Category="Inventory")
	TObjectPtr<UStructureInventory> Inventory;

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

	AStructure();

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

	COMPONENT_ACCESSOR_NAME(SectorLocation, Location);
	COMPONENT_ACCESSOR(Affiliation);
	COMPONENT_ACCESSOR(Dockable);
	COMPONENT_ACCESSOR(Targetable);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	UStructureInventory* GetInventory() const;

	UFUNCTION(BlueprintCallable)
	UStructureGameplay* GetGameplay() const;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	float PropagateDamage(AStructurePart* Part, float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

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

	UFUNCTION(BlueprintCallable)
	UStaticMeshComponent* GetStaticMesh() const;
	
	UFUNCTION(BlueprintCallable, Category="Camera")
	USpringArmComponent* GetCameraSpringArm() const;

protected:

	virtual void SetActorHiddenInGame(bool bNewHidden) override;

	UFUNCTION()
	void HandlePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, const FVector HitLocation, UPrimitiveComponent* HitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser);

private:

	FVector CalculateImpulse(const FVector& RawVelocities, const FVector& RawInput, float MaxSpeed, float Accel, float DeltaTime) const;

};
