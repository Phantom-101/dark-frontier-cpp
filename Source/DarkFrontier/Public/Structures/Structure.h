// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Structure.generated.h"

DECLARE_MULTICAST_DELEGATE(FStructureStateChanged)

UCLASS()
class DARKFRONTIER_API AStructure : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AStructure();

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components")
	TObjectPtr<class UStructureAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components")
	TObjectPtr<class UStructureAttributeSet> Attributes;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components")
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components")
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	TArray<TSubclassOf<UGameplayEffect>> PassiveEffectClasses;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	TObjectPtr<class AStructurePart> RootPart;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	TArray<TObjectPtr<AStructurePart>> Parts;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Input")
	FVector MoveInput = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Input")
	FVector RotateInput = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Combat")
	TObjectPtr<class AFaction> OwningFaction;

public:

	FStructureStateChanged OnLayoutChanged;

	FStructureStateChanged OnActionsChanged;
	
protected:

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
public:

	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintCallable, Category="Lifetime")
	bool TryInit(AStructurePart* NewRoot, bool RegisterOnly = false);

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

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	float GetUpkeep() const;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	bool IsDetecting(AStructure* Other) const;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	struct FActiveGameplayEffectHandle ApplyEffect(TSubclassOf<class UGameplayEffect> EffectClass);

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	struct FGameplayAbilitySpecHandle GrantAbility(TSubclassOf<class UStructureGameplayAbility> AbilityClass);

	UFUNCTION(BlueprintCallable, Category="Input")
	void SetMoveInput(FVector InInput);

	UFUNCTION(BlueprintCallable, Category="Input")
	void SetRotateInput(FVector InInput);
	
	UFUNCTION(BlueprintCallable, Category="Combat")
	AFaction* GetOwningFaction() const;

	UFUNCTION(BlueprintCallable, Category="Combat")
	void SetOwningFaction(AFaction* InFaction);
	
	UFUNCTION(BlueprintCallable, Category="Camera")
	USpringArmComponent* GetCameraSpringArm() const;

protected:
	
	FVector CalculateImpulse(const FVector& RawVelocities, const FVector& RawInput, float MaxSpeed, float Accel, float DeltaTime) const;
	
};
