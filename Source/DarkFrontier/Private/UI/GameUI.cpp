// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/GameUI.h"
#include "AbilitySystemComponent.h"
#include "ActiveGameplayEffectHandle.h"
#include "CommonListView.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Structures/Structure.h"
#include "UI/CustomGameplayEffectUIData.h"
#include "UI/GameplayEffectIndicatorObject.h"

TOptional<FUIInputConfig> UGameUI::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::Game, EMouseCaptureMode::CapturePermanently);
}

void UGameUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(const AStructure* PlayerStructure = Cast<AStructure>(GetOwningPlayerPawn()))
	{
		const FVector ScaledRotateInput = PlayerStructure->RotateAddInput * 200;
		UWidgetLayoutLibrary::SlotAsCanvasSlot(TurnIndicator)->SetPosition(FVector2D(ScaledRotateInput.Z, ScaledRotateInput.Y));

		TArray<FActiveGameplayEffectHandle> Existing;
		for(UObject* Object : GameplayEffectIndicators->GetListItems())
		{
			UGameplayEffectIndicatorObject* Casted = Cast<UGameplayEffectIndicatorObject>(Object);
			if(Casted->EffectHandle.IsValid() && Casted->EffectHandle.GetOwningAbilitySystemComponent() != nullptr)
			{
				Existing.Add(Casted->EffectHandle);
			}
			else
			{
				GameplayEffectIndicators->RemoveItem(Casted);
			}
		}
		
		for(FActiveGameplayEffectHandle Handle : PlayerStructure->GetAbilitySystemComponent()->GetActiveGameplayEffects().GetAllActiveEffectHandles())
		{
			if(!Existing.Contains(Handle) && Cast<UCustomGameplayEffectUIData>(Handle.GetOwningAbilitySystemComponent()->GetGameplayEffectCDO(Handle)->UIData))
			{
				UGameplayEffectIndicatorObject* Object = NewObject<UGameplayEffectIndicatorObject>();
				Object->Init(Handle);
				GameplayEffectIndicators->AddItem(Object);
			}
		}
	}
}
