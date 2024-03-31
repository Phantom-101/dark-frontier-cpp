// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/GameUI/GameUI.h"
#include "AbilitySystemComponent.h"
#include "ActiveGameplayEffectHandle.h"
#include "CommonButtonBase.h"
#include "CommonListView.h"
#include "Log.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Structures/Structure.h"
#include "Structures/StructureController.h"
#include "UI/CustomGameplayEffectUIData.h"
#include "UI/GameplayEffectIndicatorObject.h"
#include "UI/Screens/GameUI/StructureAbilityButtonList.h"

TOptional<FUIInputConfig> UGameUI::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::Game, EMouseCaptureMode::CapturePermanently);
}

void UGameUI::NativeConstruct()
{
	Super::NativeConstruct();

	if(AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController()))
	{
		Controller->OnLayoutChanged.AddUObject<UGameUI>(this, &UGameUI::UpdateAbilities);
		UpdateAbilities();
	}
	else
	{
		UE_LOG(LogDarkFrontier, Warning, TEXT("Structure controller not found"));
	}
}

void UGameUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{  
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(const AStructureController* PlayerController = Cast<AStructureController>(GetWorld()->GetFirstPlayerController()))
	{
		const FVector ScaledRotateInput = PlayerController->GetTurnIndicatorOffset() * 200;
		UWidgetLayoutLibrary::SlotAsCanvasSlot(TurnIndicator)->SetPosition(FVector2D(ScaledRotateInput.Z, ScaledRotateInput.Y));
	}

	if(const AStructure* PlayerStructure = Cast<AStructure>(GetOwningPlayerPawn()))
	{
		TArray<FActiveGameplayEffectHandle> Existing;
		for(UObject* Object : GameplayEffectList->GetListItems())
		{
			UGameplayEffectIndicatorObject* Casted = Cast<UGameplayEffectIndicatorObject>(Object);
			if(Casted->EffectHandle.IsValid() && IsValid(Casted->EffectHandle.GetOwningAbilitySystemComponent()))
			{
				Existing.Add(Casted->EffectHandle);
			}
			else
			{
				GameplayEffectList->RemoveItem(Casted);
			}
		}
		
		for(FActiveGameplayEffectHandle Handle : PlayerStructure->GetAbilitySystemComponent()->GetActiveGameplayEffects().GetAllActiveEffectHandles())
		{
			if(!Existing.Contains(Handle) && Cast<UCustomGameplayEffectUIData>(Handle.GetOwningAbilitySystemComponent()->GetGameplayEffectCDO(Handle)->UIData))
			{
				UGameplayEffectIndicatorObject* Object = NewObject<UGameplayEffectIndicatorObject>();
				Object->Init(Handle);
				GameplayEffectList->AddItem(Object);
			}
		}
	}
}

void UGameUI::UpdateAbilities() const
{
	if(const AStructureController* Controller = Cast<AStructureController>(GetWorld()->GetFirstPlayerController()))
	{
		AbilityButtonList->UpdateButtons(Cast<AStructure>(Controller->GetPawn()));
	}
}
