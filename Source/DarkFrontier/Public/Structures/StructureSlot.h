// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "StructureSlot.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKFRONTIER_API UStructureSlot : public USceneComponent
{
	GENERATED_BODY()

public:

	UStructureSlot();

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	FText SlotName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	TObjectPtr<class UStructureSlotType> SlotType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Instanced, Category="Setup")
	TObjectPtr<class UStructureSlotFilter> Filter;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AStructurePart> OwningPart;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UStructureSlot> AttachedSlot;

	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable, Category="Prototype")
	FText GetSlotName() const;
	
	UFUNCTION(BlueprintCallable, Category="Prototype")
	UStructureSlotType* GetSlotType() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	class AStructure* GetOwningStructure() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	AStructurePart* GetOwningPart() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	UStructureSlot* GetAttachedSlot() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	bool CanAttach(const UStructureSlot* Other) const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	bool TryAttach(UStructureSlot* NewSlot, bool SuppressUpdate = false);
	
	UFUNCTION(BlueprintCallable, Category="Layout")
	bool TryDetach();

protected:

	UFUNCTION(BlueprintCallable)
	void MatchTransform(UStructureSlot* Other);
	
};
