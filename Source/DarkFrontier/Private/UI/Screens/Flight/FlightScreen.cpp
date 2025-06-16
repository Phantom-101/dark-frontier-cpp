// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Flight/FlightScreen.h"
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
#include "Structures/StructureDock.h"
#include "Structures/StructureGameplay.h"
#include "Structures/StructureLayout.h"
#include "Structures/StructureLocation.h"
#include "Structures/StructurePart.h"
#include "UI/Screens/Flight/Controls/StructurePartControls.h"
#include "UI/Screens/Flight/Controls/StructurePartControlsMapping.h"
#include "UI/Screens/Flight/Selectors/StructureSelectors.h"
#include "UI/Widgets/Visuals/Arc.h"
#include "UI/Widgets/Visuals/CustomGameplayEffectUIData.h"
#include "UI/Widgets/Visuals/GameplayEffectIndicatorObject.h"

TOptional<FUIInputConfig> UFlightScreen::GetDesiredInputConfig() const
{
	if(const AStructureController* Controller = GetWorld()->GetFirstPlayerController<AStructureController>())
	{
		if(Controller->GetIsCursorUnlocked())
		{
			return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture);
		}
	}
	return FUIInputConfig(ECommonInputMode::Game, EMouseCaptureMode::CapturePermanently);
}

void UFlightScreen::NativeConstruct()
{
	Super::NativeConstruct();

	DockButton->OnClicked().AddUObject<UFlightScreen>(this, &UFlightScreen::HandleDock);
}

void UFlightScreen::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
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
			UStructureGameplay* Gameplay = Structure->GetGameplay();
			
			HullArc->SetLength(Gameplay->GetHull() / Gameplay->GetMaxHull() * 0.25);
			ShieldArc->SetLength(Gameplay->GetShield() / Gameplay->GetMaxShield() * 0.2);
			EnergyArc->SetLength(Gameplay->GetEnergy() / Gameplay->GetMaxEnergy() * 0.25);
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

	const AStructure* PlayerStructure = Cast<AStructure>(GetOwningPlayerPawn());
	if(IsValid(PlayerStructure))
	{
		TArray<AStructurePart*> Existing;
		for(UWidget* Widget : PartControls->GetAllChildren())
		{
			UStructurePartControls* Control = Cast<UStructurePartControls>(Widget);
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

		for(AStructurePart* Part : PlayerStructure->GetLayout()->GetParts())
		{
			if(!Existing.Contains(Part))
			{
				TSubclassOf<UStructurePartControls> ControlsClass = ControlsMapping->Map(Part->GetClass());
				if(ControlsClass != nullptr)
				{
					UStructurePartControls* Controls = CreateWidget<UStructurePartControls>(this, ControlsClass);
					Controls->TryInitialize(Part);
					if(Controls->GetPart() == Part)
					{
						PartControls->AddChild(Controls);
					}
					else
					{
						Controls->BeginDestroy();
					}
				}
			}
		}
	}
}

void UFlightScreen::HandleDock() const
{
	const AStructure* PlayerStructure = Cast<AStructure>(GetOwningPlayerPawn());
	if(IsValid(PlayerStructure) && IsValid(PlayerStructure->GetTarget()))
	{
		for(UStructureDock* Dock : PlayerStructure->GetTarget()->GetLayout()->GetFacilities<UStructureDock>())
		{
			if(PlayerStructure->GetLocation()->EnterDock(Dock))
			{
				break;
			}
		}
	}
}
