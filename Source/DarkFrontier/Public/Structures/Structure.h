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

	UPROPERTY(BlueprintReadOnly);
	TObjectPtr<class AStructureSection> RootSection;

	UPROPERTY(BlueprintReadOnly);
	TArray<TObjectPtr<AStructureSection>> Sections;

	UPROPERTY()
	int32 NextSectionId;

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
	TObjectPtr<class AActor> CameraTarget;

	virtual void Tick(float DeltaTime) override;
	
public:

	UFUNCTION(BlueprintCallable)
	void InitRootSection(AStructureSection* NewRoot);

	UFUNCTION(BlueprintCallable)
	AStructureSection* GetRootSection();

	UFUNCTION(BlueprintCallable)
	void RegisterSection(AStructureSection* Section);

	UFUNCTION(BlueprintCallable)
	void UnregisterSection(AStructureSection* Section);

	UFUNCTION(BlueprintCallable)
	void UpdateSections();

	UFUNCTION(BlueprintCallable)
	TArray<AStructureSection*> GetCachedSections();

	UFUNCTION(BlueprintCallable)
	TArray<AStructureSection*> GetConnectedSections();

	UFUNCTION(BlueprintCallable)
	bool IsLayoutValid();

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
