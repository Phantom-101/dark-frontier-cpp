// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureController.h"
#include "EnhancedInputComponent.h"
#include "Input/CommonUIActionRouterBase.h"
#include "Structures/Structure.h"
#include "UI/StructureBuilder.h"
#include "UI/Screens/StructureDetails/StructureDetails.h"
#include "UI/UIBase.h"

AStructureController::AStructureController()
{
}

void AStructureController::BeginPlay()
{
	Super::BeginPlay();

	UIBaseWidget = CreateWidget<UUIBase>(GetGameInstance(), UIBaseClass);
	UIBaseWidget->AddToViewport();
	(void)UIBaseWidget->PushGame(GameUIClass);
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
	Input->BindAction(EditStructureAction, ETriggerEvent::Completed, this, &AStructureController::EditStructure);
}

void AStructureController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/*
	if(const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
    {
    	if (const UCommonUIActionRouterBase* Router = LocalPlayer->GetSubsystem<UCommonUIActionRouterBase>())
    	{
    		if (Router)
    		{
    			Router->GetActiveInputMode();
    			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, FString::Printf(TEXT("current input mode: %s"), LexToString(Router->GetActiveInputMode())));
			    const EMouseCaptureMode CaptureMode = Router->GetActiveMouseCaptureMode();
    			FString Str;
    			switch (CaptureMode)
    			{
    			case EMouseCaptureMode::NoCapture: Str = "NoCapture"; break;
			    case EMouseCaptureMode::CapturePermanently: Str = "CapturePermanently"; break;
			    case EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown: Str = "CapturePermanently_IncludingInitialMouseDown"; break;
			    case EMouseCaptureMode::CaptureDuringMouseDown: Str = "CaptureDuringMouseDown"; break;
			    case EMouseCaptureMode::CaptureDuringRightMouseDown: Str = "CaptureDuringRightMouseDown"; break;
			    default: ;
			    }
    			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, FString::Printf(TEXT("current capture mode: %s"), *Str));
    		}
    	}
    }
    */
}

void AStructureController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	StructurePawn = Cast<AStructure>(GetPawn());

	if(StructurePawn)
	{
		StructurePawn->OnLayoutChanged.BindUObject<AStructureController>(this, &AStructureController::PropagateLayoutChange);
		StructurePawn->OnActionsChanged.BindUObject<AStructureController>(this, &AStructureController::PropagateActionsChange);
	}
}

void AStructureController::OnUnPossess()
{
	Super::OnUnPossess();

	if(StructurePawn)
	{
		StructurePawn->OnLayoutChanged.Unbind();
		StructurePawn->OnActionsChanged.Unbind();
	}

	StructurePawn = nullptr;
}

void AStructureController::Move(const FInputActionInstance& Instance)
{
	if(StructurePawn)
	{
		StructurePawn->Move(Instance.GetValue().Get<FVector>());
	}
}

void AStructureController::RotateAdd(const FInputActionInstance& Instance)
{
	if(StructurePawn && !IsCursorUnlocked)
	{
		StructurePawn->RotateAdd(Instance.GetValue().Get<FVector>());
	}
}

void AStructureController::RotateOverride(const FInputActionInstance& Instance)
{
	if(StructurePawn)
	{
		StructurePawn->RotateOverride(Instance.GetValue().Get<FVector>());
	}
}

void AStructureController::Look(const FInputActionInstance& Instance)
{
	if(StructurePawn)
	{
		StructurePawn->Look(Instance.GetValue().Get<FVector2D>());
	}
}

void AStructureController::Zoom(const FInputActionInstance& Instance)
{
	if(StructurePawn)
	{
		StructurePawn->Zoom(Instance.GetValue().Get<float>());
	}
}

void AStructureController::ToggleUnlock(const FInputActionInstance& Instance)
{
	IsCursorUnlocked = !IsCursorUnlocked;
	
	if(const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UCommonUIActionRouterBase* Router = LocalPlayer->GetSubsystem<UCommonUIActionRouterBase>())
		{
			if (Router)
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

void AStructureController::EditStructure(const FInputActionInstance& Instance)
{
	UStructureDetails* Details = UIBaseWidget->PushGame<UStructureDetails>(StructureDetailsUIClass);
	Details->Select(StructurePawn);
	Details->Init(AvailableParts);
}

void AStructureController::PropagateLayoutChange()
{
	if(OnLayoutChanged.IsBound())
	{
		OnLayoutChanged.Execute();
	}
}

void AStructureController::PropagateActionsChange()
{
	if(OnActionsChanged.IsBound())
	{
		OnActionsChanged.Execute();
	}
}
