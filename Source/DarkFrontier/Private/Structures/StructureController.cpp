// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures/StructureController.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Input/CommonUIActionRouterBase.h"
#include "Structures/Structure.h"
#include "UI/StructureBuilder.h"
#include "UI/Screens/StructureDetails/StructureDetails.h"
#include "UI/Screens/UIBase.h"

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

	StructurePawn->SetMoveInput(MoveInput);
	StructurePawn->SetRotateInput(RotateAddInput + RotateOverrideInput);
	
	UpdateCamera();
}

void AStructureController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	StructurePawn = Cast<AStructure>(InPawn);

	if(StructurePawn)
	{
		StructurePawn->GetAbilitySystemComponent()->InitAbilityActorInfo(StructurePawn, StructurePawn);
		
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

void AStructureController::UpdateCamera()
{
	if(StructurePawn == nullptr) return;
	
	if(LookTarget == nullptr)
	{
		LookTarget = StructurePawn;
	}
	
	FBoxSphereBounds Bounds;
	if(const AStructure* TargetStructure = Cast<AStructure>(LookTarget))
	{
		Bounds = GetStructureViewBounds(TargetStructure, true);
	}
	else
	{
		Bounds = GetViewBounds(LookTarget, true);
	}

	USpringArmComponent* SpringArm = StructurePawn->GetCameraSpringArm();
	
	SpringArm->SetRelativeLocation(StructurePawn->GetTransform().InverseTransformPosition(LookTarget->GetActorLocation()));
	SpringArm->TargetArmLength = Bounds.SphereRadius * 2 * ZoomLevel;

	SpringArm->SetWorldRotation(LookTarget->GetActorRotation());
	SpringArm->AddLocalRotation(FRotator(LookRotation.Y, LookRotation.X, 0));
}

FBoxSphereBounds AStructureController::GetViewBounds(const AActor* Actor, const bool OnlyCollidingComponents)
{
	FBoxSphereBounds Bounds;
	Actor->ForEachComponent<UPrimitiveComponent>(false, [&](const UPrimitiveComponent* InPrimComp)
	{
		if (InPrimComp->IsRegistered() && (!OnlyCollidingComponents || InPrimComp->IsCollisionEnabled()))
		{
			Bounds = Bounds + InPrimComp->Bounds;
		}
	});
	return Bounds;
}

FBoxSphereBounds AStructureController::GetStructureViewBounds(const AStructure* Structure, const bool OnlyCollidingComponents)
{
	FBoxSphereBounds Bounds;
	TArray<AActor*> AttachedActors;
	Structure->GetAttachedActors(AttachedActors);
	for (const AActor* AttachedActor : AttachedActors)
	{
		Bounds = Bounds + GetViewBounds(AttachedActor, OnlyCollidingComponents);
	}
	return Bounds;
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
	LookRotation = FVector2D(FMath::Fmod(LookRotation.X + Value.X, 360), FMath::Clamp(LookRotation.Y + Value.Y, -90, 90));
}

void AStructureController::Zoom(const FInputActionInstance& Instance)
{
	ZoomLevel = FMath::Clamp(ZoomLevel + Instance.GetValue().Get<float>(), 1.5, 10);
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
