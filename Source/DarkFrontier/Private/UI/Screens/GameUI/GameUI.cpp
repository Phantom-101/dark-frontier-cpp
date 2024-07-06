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
#include "Components/ScrollBox.h"
#include "Structures/Structure.h"
#include "Structures/StructureController.h"
#include "Structures/StructurePart.h"
#include "UI/Widgets/CustomGameplayEffectUIData.h"
#include "UI/Widgets/GameplayEffectIndicatorObject.h"
#include "UI/Screens/GameUI/StructurePartIndicator.h"
#include "UI/Screens/GameUI/StructureSelectionLayer.h"
#include "UI/Widgets/Arc.h"

TOptional<FUIInputConfig> UGameUI::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::Game, EMouseCaptureMode::CapturePermanently);
}

void UGameUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{  
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(!IsValid(GetOwningPlayerPawn()))
	{
		UE_LOG(LogDarkFrontier, Warning, TEXT("Game UI pawn is invalid, skipping tick"));
		return;
	}

	if(const AStructureController* PlayerController = Cast<AStructureController>(GetWorld()->GetFirstPlayerController()))
	{
		if(const AStructure* Structure = Cast<AStructure>(PlayerController->GetPawn()))
		{
			HullArc->SetLength(Structure->GetHull() / Structure->GetMaxHull() * 0.25);
			ShieldArc->SetLength(Structure->GetShield() / Structure->GetMaxShield() * 0.2);
			EnergyArc->SetLength(Structure->GetEnergy() / Structure->GetMaxEnergy() * 0.25);
			SpeedArc->SetLength(Structure->GetLinearSpeed() / Structure->GetLinearMaxSpeed() * 0.2);
		}
		
		const FVector ScaledRotateInput = PlayerController->GetTurnIndicatorOffset() * 200;
		UWidgetLayoutLibrary::SlotAsCanvasSlot(TurnIndicator)->SetPosition(FVector2D(ScaledRotateInput.Z, ScaledRotateInput.Y));
	}

	if(const AStructure* PlayerStructure = Cast<AStructure>(GetOwningPlayerPawn()))
	{
		TArray<FActiveGameplayEffectHandle> Existing;
		TArray<UGameplayEffectIndicatorObject*> ToRemove;
		for(UObject* Object : GameplayEffectList->GetListItems())
		{
			UGameplayEffectIndicatorObject* Casted = Cast<UGameplayEffectIndicatorObject>(Object);
			if(Casted->EffectHandle.IsValid() && IsValid(Casted->EffectHandle.GetOwningAbilitySystemComponent()))
			{
				Existing.Add(Casted->EffectHandle);
			}
			else
			{
				ToRemove.Add(Casted);
			}
		}

		for(UGameplayEffectIndicatorObject* Obj : ToRemove)
		{
			GameplayEffectList->RemoveItem(Obj);
		}
		
		for(FActiveGameplayEffectHandle Handle : PlayerStructure->GetAbilitySystemComponent()->GetActiveGameplayEffects().GetAllActiveEffectHandles())
		{
			if(!Existing.Contains(Handle) && Cast<UCustomGameplayEffectUIData>(Handle.GetOwningAbilitySystemComponent()->GetGameplayEffectCDO(Handle)->UIData))
			{
				UGameplayEffectIndicatorObject* Object = NewObject<UGameplayEffectIndicatorObject>();
				Object->EffectHandle = Handle;
				GameplayEffectList->AddItem(Object);
			}
		}
	}

	SelectionLayer->UpdateSelectors();

	if(AStructure* PlayerStructure = Cast<AStructure>(GetOwningPlayerPawn()))
	{
		TArray<AStructurePart*> Existing;
		for(UWidget* Widget : PartIndicators->GetAllChildren())
		{
			UStructurePartIndicator* Indicator = Cast<UStructurePartIndicator>(Widget);
			if(IsValid(Indicator))
			{
				if(IsValid(Indicator->GetPart()))
				{
					Existing.Add(Indicator->GetPart());
				}
				else
				{
					PartIndicators->RemoveChild(Indicator);
				}
			}
			else
			{
				UE_LOG(LogDarkFrontier, Warning, TEXT("Non indicator widget of type %s found in indicators list, removing"), *Widget->GetClass()->GetDisplayNameText().ToString())
				PartIndicators->RemoveChild(Widget);
			}
		}

		for(AStructurePart* Part : PlayerStructure->GetParts())
		{
			if(!Existing.Contains(Part))
			{
				UStructurePartIndicator* Indicator = Part->CreateIndicator(PartIndicators);
				if(Indicator != nullptr)
				{
					PartIndicators->AddChild(Indicator);
				}
			}
		}
	}
}
