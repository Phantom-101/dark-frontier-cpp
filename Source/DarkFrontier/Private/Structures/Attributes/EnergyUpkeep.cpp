// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/Attributes/EnergyUpkeep.h"
#include "Structures/StructureAttributeSet.h"

UEnergyUpkeep::UEnergyUpkeep()
{
	UpkeepDef.AttributeToCapture = UStructureAttributeSet::GetUpkeepAttribute();
	UpkeepDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	UpkeepDef.bSnapshot = false;

	UpkeepReductionDef.AttributeToCapture = UStructureAttributeSet::GetUpkeepReductionAttribute();
	UpkeepReductionDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	UpkeepReductionDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(UpkeepDef);
	RelevantAttributesToCapture.Add(UpkeepReductionDef);
}

float UEnergyUpkeep::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Upkeep = 0;
	GetCapturedAttributeMagnitude(UpkeepDef, Spec, EvaluationParameters, Upkeep);
	Upkeep = FMath::Max(Upkeep, 0);

	float UpkeepReduction = 1;
	GetCapturedAttributeMagnitude(UpkeepReductionDef, Spec, EvaluationParameters, UpkeepReduction);
	UpkeepReduction = FMath::Max(UpkeepReduction, 1);

	return Upkeep / UpkeepReduction;
}
