// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "StructurePartFilter.h"
#include "Components/SceneComponent.h"
#include "StructureSlot.generated.h"

struct FStructurePartFilter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKFRONTIER_API UStructureSlot : public USceneComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	FText SlotName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	TInstancedStruct<FStructurePartFilter> Filter = TInstancedStruct<FStructurePartFilter>::Make();

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AStructurePart> OwningPart;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UStructureSlot> AttachedSlot;

	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable, Category="Prototype")
	FText GetSlotName() const;
	
	UFUNCTION(BlueprintCallable, Category="Layout")
	class AStructure* GetOwningStructure() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	AStructurePart* GetOwningPart() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	const AStructurePart* GetOwningPart_Always() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	UStructureSlot* GetAttachedSlot() const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	bool CanAttach(const UStructureSlot* Other) const;

	UFUNCTION(BlueprintCallable, Category="Layout")
	bool TryAttach(UStructureSlot* NewSlot);
	
	UFUNCTION(BlueprintCallable, Category="Layout")
	bool TryDetach();

protected:

	UFUNCTION(BlueprintCallable)
	void MatchTransform(UStructureSlot* Other) const;

public:

	static const AStructurePart* GetOwningPart_CDO(const UStructureSlot* Slot);
	
};
