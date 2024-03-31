// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/StructureAbilityButton.h"
#include "CommonButtonBase.h"
#include "Components/Image.h"
#include "Structures/Structure.h"
#include "UI/Screens/GameUI/StructurePartAbilityClass.h"

void UStructureAbilityButton::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	AbilityClassObj = Cast<UStructurePartAbilityClass>(ListItemObject);

	if(MaterialInstance == nullptr)
	{
		MaterialInstance = UMaterialInstanceDynamic::Create(Material, this);
		RadialProgressBar->SetBrushFromMaterial(MaterialInstance);
	}

	AbilityButton->OnClicked().Clear();
	AbilityButton->OnClicked().AddUObject<UStructureAbilityButton>(this, &UStructureAbilityButton::OnAbilityButtonClicked);
}

void UStructureAbilityButton::OnAbilityButtonClicked() const
{
	if(IsValid(AbilityClassObj->TargetStructure.Get()))
	{
		AbilityClassObj->TargetStructure->ActivateAbility(AbilityClassObj);
	}
}
