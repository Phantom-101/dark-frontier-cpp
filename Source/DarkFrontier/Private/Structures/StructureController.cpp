// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureController.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "Game/UniverseGameState.h"
#include "GameFramework/SpringArmComponent.h"
#include "Input/CommonUIActionRouterBase.h"
#include "Objects/ActorViewTarget.h"
#include "Structures/Structure.h"
#include "Structures/StructureDock.h"
#include "Structures/StructureLayout.h"
#include "Structures/StructureLocation.h"
#include "UI/Screens/GameUIBase.h"
#include "UI/Screens/BuildUI/BuildUI.h"
#include "UI/Screens/UIBase.h"
#include "UI/Screens/GameUI/GameUI.h"
#include "UI/Screens/InventoryUI/InventoryUI.h"
#include "UI/Screens/StationUI/StationUI.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

AStructureController::AStructureController()
{
}

void AStructureController::BeginPlay()
{
	Super::BeginPlay();

	UIBaseWidget = CreateWidget<UUIBase>(GetGameInstance(), UIBaseClass);
	UIBaseWidget->AddToViewport();
	GameUIBaseWidget = UIBaseWidget->GetStack()->AddWidget<UGameUIBase>(GameUIBaseClass.Get());
	(void)GameUIBaseWidget->GetGameStack()->AddWidget(GameUIClass.Get());
}

void AStructureController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AStructureController::Move);
	Input->BindAction(MoveAction, ETriggerEvent::Completed, this, &AStructureController::Move);
	Input->BindAction(RotateAddAction, ETriggerEvent::Triggered, this, &AStructureController::RotateAdd);
	Input->BindAction(RotateAddAction, ETriggerEvent::Completed, this, &AStructureController::RotateAdd);
	Input->BindAction(RotateOverrideAction, ETriggerEvent::Triggered, this, &AStructureController::RotateOverride);
	Input->BindAction(RotateOverrideAction, ETriggerEvent::Completed, this, &AStructureController::RotateOverride);
	Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AStructureController::Look);
	Input->BindAction(LookAction, ETriggerEvent::Completed, this, &AStructureController::Look);
	Input->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AStructureController::Zoom);
	Input->BindAction(ZoomAction, ETriggerEvent::Completed, this, &AStructureController::Zoom);
	Input->BindAction(ToggleUnlockAction, ETriggerEvent::Completed, this, &AStructureController::ToggleUnlock);
	Input->BindAction(InventoryAction, ETriggerEvent::Completed, this, &AStructureController::OpenInventory);
	Input->BindAction(EditStructureAction, ETriggerEvent::Completed, this, &AStructureController::EditStructure);
}

void AStructureController::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(!IsValid(StructurePawn)) return;

	StructurePawn->SetMoveInput(MoveInput.IsNearlyZero(0.05) ? FVector::ZeroVector : MoveInput);
	const FVector RotateInput = RotateAddInput + RotateOverrideInput;
	StructurePawn->SetRotateInput(RotateInput.IsNearlyZero(0.05) ? FVector::ZeroVector : RotateInput);
	
	UpdateCamera();
}

void AStructureController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	StructurePawn = Cast<AStructure>(InPawn);

	if(StructurePawn)
	{
		StructurePawn->GetAbilitySystemComponent()->InitAbilityActorInfo(StructurePawn, StructurePawn);
		
		StructurePawn->GetLayout()->OnUpdated.AddUObject<AStructureController>(this, &AStructureController::PropagateLayoutChange);
		StructurePawn->GetLocation()->OnDockChanged.AddUObject<AStructureController>(this, &AStructureController::HandleDock);

		GetWorld()->GetGameState<AUniverseGameState>()->SetPlayerFaction(StructurePawn->GetOwningFaction());
	}
}

void AStructureController::OnUnPossess()
{
	Super::OnUnPossess();

	if(StructurePawn)
	{
		StructurePawn->GetLayout()->OnUpdated.RemoveAll(this);
		StructurePawn->GetLocation()->OnDockChanged.RemoveAll(this);
	}

	StructurePawn = nullptr;
}

void AStructureController::SetViewTarget(UViewTarget* InTarget)
{
	ViewTarget = InTarget;
}

bool AStructureController::GetIsCursorUnlocked() const
{
	return IsCursorUnlocked;
}

void AStructureController::UpdateCamera()
{
	if(!IsValid(StructurePawn)) return;
	
	if(ViewTarget == nullptr || !ViewTarget->IsValid())
	{
		ViewTarget = UActorViewTarget::New(StructurePawn);
	}

	const float ViewDistance = ViewTarget->GetViewDistance() * ZoomLevel;
	
	USpringArmComponent* SpringArm = StructurePawn->GetCameraSpringArm();
	
	SpringArm->SetWorldLocation(ViewTarget->GetViewLocation());
	SpringArm->TargetArmLength = ViewDistance;

	SpringArm->SetWorldRotation(ViewTarget->GetViewRotation());
	SpringArm->AddLocalRotation(FRotator(CameraRotation.Y, CameraRotation.X, 0));
}

UUIBase* AStructureController::GetUIBaseWidget() const
{
	return UIBaseWidget;
}

UGameUIBase* AStructureController::GetGameUIBaseWidget() const
{
	return GameUIBaseWidget;
}

FVector AStructureController::GetTurnIndicatorOffset() const
{
	return RotateAddInput;
}

void AStructureController::Move(const FInputActionInstance& Instance)
{
	MoveInput = Instance.GetValue().Get<FVector>().GetClampedToMaxSize(1);
}

void AStructureController::RotateAdd(const FInputActionInstance& Instance)
{
	RotateAddInput = (RotateAddInput + Instance.GetValue().Get<FVector>()).GetClampedToMaxSize(1);
}

void AStructureController::RotateOverride(const FInputActionInstance& Instance)
{
	RotateOverrideInput = Instance.GetValue().Get<FVector>().GetClampedToMaxSize(1);
}

void AStructureController::Look(const FInputActionInstance& Instance)
{
	const FVector Value = Instance.GetValue().Get<FVector>();
	CameraRotation = FVector2D(FMath::Fmod(CameraRotation.X + Value.X, 360), FMath::Clamp(CameraRotation.Y + Value.Y, -90, 90));
}

void AStructureController::Zoom(const FInputActionInstance& Instance)
{
	ZoomLevel = FMath::Clamp(ZoomLevel + Instance.GetValue().Get<float>() * 0.5, 1, 10);
}

void AStructureController::ToggleUnlock(const FInputActionInstance& Instance)
{
	IsCursorUnlocked = !IsCursorUnlocked;
	
	if(const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if(UCommonUIActionRouterBase* Router = LocalPlayer->GetSubsystem<UCommonUIActionRouterBase>())
		{
			if(Router)
			{
				if(IsCursorUnlocked)
				{
					Router->SetActiveUIInputConfig(FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture));
					int32 SizeX, SizeY;
					GetViewportSize(SizeX, SizeY);
					SetMouseLocation(SizeX / 2, SizeY / 2);
				}
				else
				{
					Router->SetActiveUIInputConfig(FUIInputConfig(ECommonInputMode::Game, EMouseCaptureMode::CapturePermanently));
				}
			}
		}
	}
}

void AStructureController::OpenInventory(const FInputActionInstance& Instance)
{
	if(!IsValid(StructurePawn)) return;

	UInventoryUI* Inventory = GameUIBaseWidget->GetGameStack()->AddWidget<UInventoryUI>(InventoryUIClass);
	Inventory->SetStructure(StructurePawn);
}

void AStructureController::EditStructure(const FInputActionInstance& Instance)
{
	if(!IsValid(StructurePawn)) return;
	
	UBuildUI* Details = GameUIBaseWidget->GetGameStack()->AddWidget<UBuildUI>(BuildUIClass);
	Details->InitStructure(StructurePawn);
	Details->SelectStructure();
	Details->SetAvailableParts(AvailableParts);
}

void AStructureController::PropagateLayoutChange() const
{
	OnLayoutChanged.Broadcast();
}

void AStructureController::HandleDock(UStructureDock* Dock) const
{
	if(!IsValid(Dock)) return;
	
	GameUIBaseWidget->GetGameStack()->AddWidget<UStationUI>(StationUIClass);
}
