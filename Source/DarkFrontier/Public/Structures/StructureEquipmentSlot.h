// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "StructureEquipmentSlot.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKFRONTIER_API UStructureEquipmentSlot : public USceneComponent
{
	GENERATED_BODY()

public:

	UStructureEquipmentSlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SlotName;

	UPROPERTY()
	TObjectPtr<class AStructureSection> OwningSection;

	UPROPERTY()
	TObjectPtr<class AStructureEquipment> AttachedEquipment;

protected:

	virtual void BeginPlay() override;
	
public:

	UFUNCTION(BlueprintCallable)
	void Attach(AStructureEquipment* NewEquipment);

};
