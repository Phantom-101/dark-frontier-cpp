// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "StructurePartSlot.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKFRONTIER_API UStructurePartSlot : public USceneComponent
{
	GENERATED_BODY()

public:

	UStructurePartSlot();

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	FText SlotName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	TObjectPtr<class UStructurePartSlotType> SlotType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Instanced, Category="Setup")
	TObjectPtr<class UStructurePartSlotFilter> Filter;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AStructurePart> OwningPart;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UStructurePartSlot> AttachedSlot;

	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable, Category="Prototype")
	FText GetSlotName() const;
	
	UFUNCTION(BlueprintCallable, Category="Prototype")
	UStructurePartSlotType* GetSlotType() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	class AStructure* GetOwningStructure() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	AStructurePart* GetOwningPart() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	UStructurePartSlot* GetAttachedSlot() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	bool CanAttach(const UStructurePartSlot* Other) const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	bool TryAttach(UStructurePartSlot* NewSlot);
	
	UFUNCTION(BlueprintCallable, Category="Layout")
	bool TryDetach();

protected:

	UFUNCTION(BlueprintCallable)
	void MatchTransform(UStructurePartSlot* Other);
	
};
