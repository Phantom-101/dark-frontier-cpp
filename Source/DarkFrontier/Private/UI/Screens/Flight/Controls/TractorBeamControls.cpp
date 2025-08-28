// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Flight/Controls/TractorBeamControls.h"
#include "CommonButtonBase.h"
#include "Macros.h"
#include "Libraries/GameFunctionLibrary.h"
#include "Structures/StructureController.h"
#include "Structures/TractorBeam.h"

void UTractorBeamControls::NativeConstruct()
{
	Super::NativeConstruct();

	ToggleButton->OnClicked().Clear();
	ToggleButton->OnClicked().AddUObject<UTractorBeamControls>(this, &UTractorBeamControls::Toggle);
}

void UTractorBeamControls::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	const AStructureController* Controller = Cast<AStructureController>(GetOwningPlayer());
	if(IsValid(Controller))
	{
		const ATractorBeam* Beam = Cast<ATractorBeam>(Part);
		if(!IsValid(Beam))
		{
			ToggleButton->SetIsEnabled(false);
			return;
		}
		if(Beam->IsActivated())
		{
			ToggleButton->SetIsEnabled(Beam->CanDeactivate());
		}
		else
		{
			ToggleButton->SetIsEnabled(Beam->CanActivate(Controller->GetSelectTarget()));
		}
	}
	else
	{
		ToggleButton->SetIsEnabled(false);
	}
}

void UTractorBeamControls::Toggle() const
{
	const AStructureController* Controller = UGameFunctionLibrary::GetPlayerController(this);
	ATractorBeam* Beam = Cast<ATractorBeam>(Part);
	GUARD(IsValid(Controller) && IsValid(Beam));
	if(Beam->IsActivated())
	{
		Beam->TryDeactivate();
	}
	else
	{
		Beam->TryActivate(Controller->GetSelectTarget());
	}
}
