// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Structures/Structure.h"
#include "UI/StructureBuilder.h"
#include "UI/UIBase.h"

AStructureController::AStructureController()
{
}

void AStructureController::BeginPlay()
{
	Super::BeginPlay();

	// Move to PawnClientRestart?
	if(const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMapping)
			{
				InputSystem->AddMappingContext(InputMapping, 0);
			}
		}
	}

	UIBaseWidget = CreateWidget<UUIBase>(GetGameInstance(), UIBaseClass);
	UIBaseWidget->AddToViewport();
	UIBaseWidget->PushGame(GameUIClass);
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
	Input->BindAction(UnlockCursorAction, ETriggerEvent::Triggered, this, &AStructureController::UnlockCursor);
	Input->BindAction(UnlockCursorAction, ETriggerEvent::Completed, this, &AStructureController::UnlockCursor);
	// todo remove completed event
	Input->BindAction(EditStructureAction, ETriggerEvent::Started, this, &AStructureController::EditStructure);
}

void AStructureController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AStructureController::Move(const FInputActionInstance& Instance)
{
	if(Cast<AStructure>(GetPawn()))
	{
		Cast<AStructure>(GetPawn())->Move(Instance.GetValue().Get<FVector>());
	}
}

void AStructureController::RotateAdd(const FInputActionInstance& Instance)
{
	if(Cast<AStructure>(GetPawn()))
	{
		Cast<AStructure>(GetPawn())->RotateAdd(Instance.GetValue().Get<FVector>());
	}
}

void AStructureController::RotateOverride(const FInputActionInstance& Instance)
{
	if(Cast<AStructure>(GetPawn()))
	{
		Cast<AStructure>(GetPawn())->RotateOverride(Instance.GetValue().Get<FVector>());
	}
}

void AStructureController::Look(const FInputActionInstance& Instance)
{
	if(Cast<AStructure>(GetPawn()))
	{
		Cast<AStructure>(GetPawn())->Look(Instance.GetValue().Get<FVector2D>());
	}
}

void AStructureController::UnlockCursor(const FInputActionInstance& Instance)
{
	SetShowMouseCursor(Instance.GetValue().Get<bool>());
}

void AStructureController::EditStructure(const FInputActionInstance& Instance)
{
	UStructureBuilder* Builder = UIBaseWidget->PushGame<UStructureBuilder>(StructureBuilderUIClass);
	Builder->SetParams(Cast<AStructure>(GetPawn()), AvailableParts);
}
