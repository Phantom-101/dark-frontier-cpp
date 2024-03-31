// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/StructureAbilityButton.h"
#include "CommonButtonBase.h"
#include "Structures/Structure.h"
#include "UI/Screens/GameUI/StructurePartAbilityClass.h"

void UStructureAbilityButton::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	AbilityClassObj = Cast<UStructurePartAbilityClass>(ListItemObject);

	AbilityButton->OnClicked().Clear();
	AbilityButton->OnClicked().AddUObject<UStructureAbilityButton>(this, &UStructureAbilityButton::OnAbilityButtonClicked);
}

void UStructureAbilityButton::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if(IsValid(AbilityClassObj->TargetStructure))
	{
		AbilityClassObj->TargetStructure->UpdateButtonMultiArc(AbilityClassObj, MultiArc);
	}
}

void UStructureAbilityButton::OnAbilityButtonClicked() const
{
	if(IsValid(AbilityClassObj->TargetStructure))
	{
		AbilityClassObj->TargetStructure->ActivateAbility(AbilityClassObj);
	}
}
