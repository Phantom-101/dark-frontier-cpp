// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Structure.generated.h"

DECLARE_DELEGATE(FStructureStateChanged)

UCLASS()
class DARKFRONTIER_API AStructure : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AStructure();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	TSubclassOf<UGameplayEffect> RegenEffect;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class AFaction> OwningFaction;

protected:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	TObjectPtr<class AStructurePart> RootPart;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	TArray<TObjectPtr<AStructurePart>> CachedParts;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	int32 NextPartId;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Layout")
	TArray<TObjectPtr<class UStructurePartActionGroup>> ActionGroups;

public:

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Input")
	FVector MoveInput;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Input")
	FVector RotateAddInput;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category="Input")
	FVector RotateOverrideInput;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GAS", meta=(AllowPrivateAccess="true"))
	TObjectPtr<class UStructureAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<class UStructureAttributeSet> Attributes;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UStaticMeshComponent> StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	TObjectPtr<AActor> CameraTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	FVector2D LookRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	float ZoomLevel = 2.5;

public:

	FStructureStateChanged OnLayoutChanged;

	FStructureStateChanged OnActionsChanged;
	
protected:

	virtual void BeginPlay() override;
	
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
	class UStructurePartAction* RegisterAction(TSubclassOf<UStructurePartActionGroup> GroupType, TSubclassOf<UStructurePartAction> ActionType);

	UFUNCTION(BlueprintCallable)
	void UnregisterAction(TSubclassOf<UStructurePartActionGroup> GroupType, UStructurePartAction* InAction);

	UFUNCTION(BlueprintCallable)
	TArray<UStructurePartActionGroup*> GetActionGroups();

	UFUNCTION(BlueprintCallable)
	TArray<AStructurePart*> GetCachedParts();
	
	UFUNCTION(BlueprintCallable)
	void UpdateCachedParts();

	UFUNCTION(BlueprintCallable)
	TArray<AStructurePart*> GetConnectedParts() const;

	UFUNCTION(BlueprintCallable)
	bool IsPartLayoutValid();

	UFUNCTION(BlueprintCallable)
	void UpdatePartDistances();

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
	void Zoom(float Value);

	UFUNCTION(BlueprintCallable)
	void SetCameraTarget(AActor* NewTarget);

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:
	
	FVector CalculateImpulse(FVector RawVelocities, FVector RawInput, float MaxSpeed, float Accel, float DeltaTime) const;

	void UpdateCameraPosition();

	FBoxSphereBounds GetStructureBounds(bool OnlyCollidingComponents) const;

	static FBoxSphereBounds GetBounds(const AActor* Actor, bool OnlyCollidingComponents);
	
};
