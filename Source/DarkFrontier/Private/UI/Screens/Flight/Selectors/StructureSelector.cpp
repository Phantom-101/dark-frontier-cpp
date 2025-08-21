// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Flight/Selectors/StructureSelector.h"
#include "Structures/Structure.h"
#include "UI/Screens/Flight/Indicators/StructureIndicators.h"

void UStructureSelector::Init(const TScriptInterface<ITargetable>& InTarget)
{
	AStructure* Structure = Cast<AStructure>(InTarget.GetObject());
	if(!ensureMsgf(IsValid(Structure), TEXT("Null or invalid target passed to structure selector")))
	{
		return;
	}

	Super::Init(InTarget);

	// Manually sync indications as existing indications are not broadcast to new selector
	for(UStructureIndication* Indication : Structure->GetIndications())
	{
		Indicators->AddIndicator(Indication);
	}

	Structure->OnIndicationAdded.AddUObject<UStructureSelector>(this, &UStructureSelector::OnIndicationAdded);
	Structure->OnIndicationRemoved.AddUObject<UStructureSelector>(this, &UStructureSelector::OnIndicationRemoved);
}

void UStructureSelector::OnIndicationAdded(UStructureIndication* Indication) const
{
	Indicators->AddIndicator(Indication);
}

void UStructureSelector::OnIndicationRemoved(UStructureIndication* Indication) const
{
	Indicators->RemoveIndicator(Indication);
}
