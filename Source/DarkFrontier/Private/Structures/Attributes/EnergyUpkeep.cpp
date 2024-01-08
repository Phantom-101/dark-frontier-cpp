// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Attributes/EnergyUpkeep.h"
#include "Structures/StructureAttributeSet.h"

UEnergyUpkeep::UEnergyUpkeep()
{
	EnergyUpkeepDefinition.AttributeToCapture = UStructureAttributeSet::GetEnergyUpkeepAttribute();
	EnergyUpkeepDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	EnergyUpkeepDefinition.bSnapshot = false;

	EnergyUpkeepReductionDefinition.AttributeToCapture = UStructureAttributeSet::GetEnergyUpkeepReductionAttribute();
	EnergyUpkeepReductionDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	EnergyUpkeepReductionDefinition.bSnapshot = false;

	RelevantAttributesToCapture.Add(EnergyUpkeepDefinition);
	RelevantAttributesToCapture.Add(EnergyUpkeepReductionDefinition);
}

float UEnergyUpkeep::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float EnergyUpkeep = 0;
	GetCapturedAttributeMagnitude(EnergyUpkeepDefinition, Spec, EvaluationParameters, EnergyUpkeep);
	EnergyUpkeep = FMath::Max(EnergyUpkeep, 0);

	float EnergyUpkeepReduction = 1;
	GetCapturedAttributeMagnitude(EnergyUpkeepReductionDefinition, Spec, EvaluationParameters, EnergyUpkeepReduction);
	EnergyUpkeepReduction = FMath::Max(EnergyUpkeepReduction, 1);

	return EnergyUpkeep / EnergyUpkeepReduction;
}


