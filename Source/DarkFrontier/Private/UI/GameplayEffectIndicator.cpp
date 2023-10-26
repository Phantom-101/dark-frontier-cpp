// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/GameplayEffectIndicator.h"

#include "AbilitySystemComponent.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "UI/CustomGameplayEffectUIData.h"
#include "UI/GameplayEffectIndicatorObject.h"

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
	if(EffectHandle.IsValid() && EffectHandle.GetOwningAbilitySystemComponent() != nullptr)
	{
		const UGameplayEffect* CDO = EffectHandle.GetOwningAbilitySystemComponent()->GetGameplayEffectCDO(EffectHandle);
		if(CDO->DurationPolicy == EGameplayEffectDurationType::Infinite)
		{
			DurationBar->SetPercent(1);
		}
		else if (CDO->DurationPolicy == EGameplayEffectDurationType::HasDuration)
		{
			const FActiveGameplayEffect* Effect = EffectHandle.GetOwningAbilitySystemComponent()->GetActiveGameplayEffect(EffectHandle);
			DurationBar->SetPercent(Effect->GetTimeRemaining(GetWorld()->GetTimeSeconds()) / Effect->GetDuration());
		}
	}
}
