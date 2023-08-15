// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureEquipmentSlot.h"
#include "Structures/StructureEquipment.h"
#include "Structures/StructureSection.h"

UStructureEquipmentSlot::UStructureEquipmentSlot()
{
}

void UStructureEquipmentSlot::BeginPlay()
{
	Super::BeginPlay();

	OwningSection = Cast<AStructureSection>(GetOwner());
	OwningSection->RegisterEquipmentSlot(this);
}

void UStructureEquipmentSlot::Attach(AStructureEquipment* NewEquipment)
{
	if(AttachedEquipment == nullptr)
	{
		AttachedEquipment = NewEquipment;
		AttachedEquipment->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
		AttachedEquipment->SetActorRelativeLocation(FVector::ZeroVector);
		AttachedEquipment->SetActorRelativeRotation(FRotator::ZeroRotator);
	}
}
