// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/StructureAbilityButton.h"
#include "AbilitySystemComponent.h"
#include "CommonButtonBase.h"
#include "Structures/Structure.h"
#include "UI/Screens/GameUI/StructureAbilityProxy.h"
#include "UI/Screens/GameUI/StructureAbilityProxyGroup.h"
#include "UI/Widgets/Arc.h"
#include "UI/Widgets/MultiArc.h"

void UStructureAbilityButton::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	ProxyGroup = Cast<UStructureAbilityProxyGroup>(ListItemObject);

	AbilityButton->OnClicked().Clear();
	AbilityButton->OnClicked().AddUObject<UStructureAbilityButton>(this, &UStructureAbilityButton::OnAbilityButtonClicked);

	MultiArc->ClearArcs();
	Arcs.Empty();
	if(IsValid(ProxyGroup->TargetStructure))
	{
		for(int Index = 0; Index < ProxyGroup->Proxies.Num(); Index++)
		{
			Arcs.Add(MultiArc->AddArc());
		}
	}
}

void UStructureAbilityButton::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if(IsValid(ProxyGroup->TargetStructure))
	{
		const float ArcLength = 1.0 / Arcs.Num();
		const float ArcPadding = FMath::Min(ArcLength * 0.1, 0.025);
		
		for(int Index = 0; Index < Arcs.Num(); Index++)
		{
			Arcs[Index]->SetStartAndLength(ArcLength * Index + ArcPadding, (ArcLength - 2 * ArcPadding) * ProxyGroup->Proxies[Index]->GetArcLength());
			// TODO set arc color
		}
	}
}

void UStructureAbilityButton::OnAbilityButtonClicked() const
{
	if(IsValid(ProxyGroup->TargetStructure))
	{
		for(UStructureAbilityProxy* Proxy : ProxyGroup->Proxies)
		{
			Proxy->TryActivate();
		}
	}
}
