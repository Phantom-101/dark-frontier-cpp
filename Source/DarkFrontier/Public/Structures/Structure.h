// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StructureTickLevel.h"
#include "GameFramework/Pawn.h"
#include "Structure.generated.h"

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

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	TArray<TSubclassOf<UGameplayEffect>> PassiveEffectClasses;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	TObjectPtr<AStructurePart> RootPart;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	TArray<TObjectPtr<AStructurePart>> Parts;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Docking")
	TObjectPtr<UStructureDock> Dock;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Sector")
	EStructureTickLevel TickLevel = EStructureTickLevel::Invalid;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Sector")
	TObjectPtr<ASector> CurrentSector;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced, Category="Inventory")
	TObjectPtr<UInventory> Inventory;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Combat")
	TObjectPtr<AFaction> OwningFaction;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Combat")
	TObjectPtr<AStructure> Target;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Gameplay")
	TObjectPtr<UStructureAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Gameplay")
	TObjectPtr<UStructureAttributeSet> Attributes;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	FGameplayTag HullDamageCueTag;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	FGameplayTag ShieldDamageCueTag;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Gameplay")
	TArray<TObjectPtr<UStructureIndication>> Indications;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TSubclassOf<UHullIndication> HullIndicationClass;

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
	bool TryInit(AStructurePart* NewRoot, bool RegisterOnly = false);

	UFUNCTION(BlueprintCallable, Category="Lifetime")
	bool TryDestroy();

	UFUNCTION(BlueprintCallable, Category="Layout")
	AStructurePart* GetRootPart() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	TArray<AStructurePart*> GetParts();

	UFUNCTION(BlueprintCallable, Category="Layout")
	AStructurePart* GetPart(FString InId);

	UFUNCTION(BlueprintCallable, Category="Layout")
	void RegisterPart(AStructurePart* InPart, bool SuppressEvent = false, bool KeepId = false);

	UFUNCTION(BlueprintCallable, Category="Layout")
	void UnregisterPart(AStructurePart* InPart, bool SuppressEvent = false);

	UFUNCTION(BlueprintCallable, Category="Layout")
	bool IsLayoutValid();

	UFUNCTION(BlueprintCallable, Category="Layout")
	bool IsLayoutSelfIntersecting();

	UFUNCTION(BlueprintCallable, Category="Layout")
	bool IsLayoutUpkeepOverloaded() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	bool LoadLayout(struct FStructureLayout InLayout);

	UFUNCTION(BlueprintCallable, Category="Layout")
	void UpdateLayoutInformation();

	UFUNCTION(BlueprintCallable, Category="Docking")
	UStructureDock* GetDock();

	UFUNCTION(BlueprintCallable, Category="Docking")
	void DockAt(UStructureDock* InDock);

	UFUNCTION(BlueprintCallable, Category="Docking")
	void UnDock();
	
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

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void InitGameplay();
	
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	float GetMaxHull() const;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	float GetHull() const;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void SetHull(float InHull) const;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	float GetMaxShield() const;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	float GetShield() const;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void SetShield(float InShield) const;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	float GetMaxEnergy() const;
	
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	float GetEnergy() const;
	
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	float GetUpkeep() const;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	float GetLinearMaxSpeed() const;
	
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	float GetLinearSpeed() const;
	
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	bool IsDetecting(AStructure* Other) const;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void ApplyDamage(FStructureDamage Damage, AStructurePart* HitPart, FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	FStructureDamage ProcessDamage(FStructureDamage Damage);

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	FStructureDamage GetHullPostMitigationDamage(const FStructureDamage& PreMitigationDamage) const;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	FStructureDamage GetShieldPostMitigationDamage(const FStructureDamage& PreMitigationDamage) const;
	
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	FActiveGameplayEffectHandle ApplyEffect(TSubclassOf<class UGameplayEffect> EffectClass) const;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	FGameplayAbilitySpecHandle GiveAbility(TSubclassOf<class UStructureAbility> AbilityClass) const;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void ClearAbility(FGameplayAbilitySpecHandle AbilityHandle) const;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

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
	
};
