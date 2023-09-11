// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Structure.generated.h"

UCLASS()
class DARKFRONTIER_API AStructure : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AStructure();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

protected:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AStructurePart> RootPart;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<AStructurePart>> CachedParts;

	UPROPERTY()
	int32 NextPartId;

public:

	UPROPERTY(BlueprintReadOnly)
	FVector MoveInput;

	UPROPERTY(BlueprintReadOnly)
	FVector RotateAddInput;

	UPROPERTY(BlueprintReadOnly)
	FVector RotateOverrideInput;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TObjectPtr<class UStructureAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<class UStructureAttributeSet> Attributes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> CameraTarget;

	virtual void Tick(float DeltaTime) override;
	
public:

	UFUNCTION(BlueprintCallable)
	void InitRootPart(AStructurePart* NewRoot);

	UFUNCTION(BlueprintCallable)
	AStructurePart* GetRootPart();

	UFUNCTION(BlueprintCallable)
	void RegisterPart(AStructurePart* InPart);

	UFUNCTION(BlueprintCallable)
	void UnregisterPart(AStructurePart* InPart);

	UFUNCTION(BlueprintCallable)
	TArray<AStructurePart*> GetCachedParts();
	
	UFUNCTION(BlueprintCallable)
	void UpdateCachedParts();

	UFUNCTION(BlueprintCallable)
	TArray<AStructurePart*> GetConnectedParts() const;

	UFUNCTION(BlueprintCallable)
	bool IsPartLayoutValid();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffect(TSubclassOf<class UGameplayEffect> EffectClass);

	UFUNCTION(BlueprintCallable)
	void GrantAbility(TSubclassOf<class UStructureGameplayAbility> AbilityClass);
	
	UFUNCTION(BlueprintCallable)
	bool IsDetecting(AStructure* Other) const;

	UFUNCTION(BlueprintCallable)
	void Move(FVector Value);
	
	UFUNCTION(BlueprintCallable)
	void RotateAdd(FVector Value);
	
	UFUNCTION(BlueprintCallable)
	void RotateOverride(FVector Value);
	
	UFUNCTION(BlueprintCallable)
	void Look(FVector2D Value);

	UFUNCTION(BlueprintCallable)
	void SetCameraTarget(AActor* NewTarget);

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:

	void UpdateAttributes();

	FVector CalculateImpulse(FVector RawVelocities, FVector RawInput, float MaxSpeed, float Accel, float DeltaTime) const;

	void UpdateCameraPosition();
	
};
