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
#include "Gameplay/Attributes/EnergyAttributeSet.h"
#include "Gameplay/Attributes/IntegrityAttributeSet.h"
#include "Structures/Structure.h"
#include "Structures/StructureController.h"
#include "Structures/StructureGameplay.h"
#include "Structures/StructureIndices.h"
#include "Structures/StructurePart.h"
#include "UI/Widgets/CustomGameplayEffectUIData.h"
#include "UI/Widgets/GameplayEffectIndicatorObject.h"
#include "UI/Screens/GameUI/StructurePartControl.h"
#include "UI/Screens/GameUI/StructureSelectors.h"
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
			const UStructureGameplay* Gameplay = Structure->GetGameplay();
			
			HullArc->SetLength(Gameplay->GetIntegrityAttributes()->GetIntegrity() / Gameplay->GetIntegrityAttributes()->GetMaxIntegrity() * 0.25);
			// TODO replace with actual shield
			ShieldArc->SetLength(Gameplay->GetIntegrityAttributes()->GetIntegrity() / Gameplay->GetIntegrityAttributes()->GetMaxIntegrity() * 0.2);
			EnergyArc->SetLength(Gameplay->GetEnergyAttributes()->GetEnergy() / Gameplay->GetEnergyAttributes()->GetMaxEnergy() * 0.25);
			// TODO replace with actual speed
			SpeedArc->SetLength(1 * 0.2);
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

	Selectors->UpdateSelectors();

	if(AStructure* PlayerStructure = Cast<AStructure>(GetOwningPlayerPawn()))
	{
		TArray<AStructurePart*> Existing;
		for(UWidget* Widget : PartControls->GetAllChildren())
		{
			UStructurePartControl* Control = Cast<UStructurePartControl>(Widget);
			if(IsValid(Control))
			{
				if(IsValid(Control->GetPart()))
				{
					Existing.Add(Control->GetPart());
				}
				else
				{
					PartControls->RemoveChild(Control);
				}
			}
			else
			{
				UE_LOG(LogDarkFrontier, Warning, TEXT("Unknown widget of type %s found in controls list, removing"), *Widget->GetClass()->GetDisplayNameText().ToString())
				PartControls->RemoveChild(Widget);
			}
		}

		for(AStructurePart* Part : PlayerStructure->GetIndices()->GetParts())
		{
			if(!Existing.Contains(Part))
			{
				UStructurePartControl* Control = Part->CreateControl(PartControls);
				if(Control != nullptr)
				{
					PartControls->AddChild(Control);
				}
			}
		}
	}
}
