// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Visuals/GameplayEffectIndicator.h"
#include "AbilitySystemComponent.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "UI/Widgets/Visuals/CustomGameplayEffectUIData.h"
#include "UI/Widgets/Visuals/GameplayEffectIndicatorObject.h"

void UGameplayEffectIndicator::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	const UGameplayEffectIndicatorObject* Object = Cast<UGameplayEffectIndicatorObject>(ListItemObject);
	EffectHandle = Object->EffectHandle;
	const UCustomGameplayEffectUIData* UIData = Cast<UCustomGameplayEffectUIData>(EffectHandle.GetOwningAbilitySystemComponent()->GetGameplayEffectCDO(Object->EffectHandle)->UIData);

	Icon->SetBrushFromTexture(UIData->Icon);
	NameText->SetText(UIData->Name);
	DescriptionText->SetText(UIData->Description);
}

void UGameplayEffectIndicator::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if(EffectHandle.IsValid() && IsValid(EffectHandle.GetOwningAbilitySystemComponent()))
	{
		const UGameplayEffect* CDO = EffectHandle.GetOwningAbilitySystemComponent()->GetGameplayEffectCDO(EffectHandle);
		if(CDO->DurationPolicy == EGameplayEffectDurationType::Infinite)
		{
			DurationBar->SetPercent(1);
		}
		else if(CDO->DurationPolicy == EGameplayEffectDurationType::HasDuration)
		{
			const FActiveGameplayEffect* Effect = EffectHandle.GetOwningAbilitySystemComponent()->GetActiveGameplayEffect(EffectHandle);
			DurationBar->SetPercent(Effect->GetTimeRemaining(GetWorld()->GetTimeSeconds()) / Effect->GetDuration());
		}
	}
}
