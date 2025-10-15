// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Screens/Info/Cargo/InfoCargoTab.h"
#include "Macros.h"
#include "Components/ListView.h"
#include "Items/Inventory.h"
#include "Items/ItemHandle.h"
#include "Libraries/ItemFunctionLibrary.h"
#include "Structures/Structure.h"
#include "Structures/StructureInventory.h"
#include "UI/Screens/Info/InfoScreen.h"
#include "UI/Widgets/Visuals/FillBar.h"

void UInfoCargoTab::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	GUARD(IsValid(Screen));

	const AStructure* Structure = Cast<AStructure>(Screen->GetActor());
	GUARD(IsValid(Structure));

	UInventory* Inventory = Structure->GetInventory();
	VolumeBar->FillHorizontal(0, Inventory->GetTotalVolume01());
	MassBar->FillHorizontal(0, Inventory->GetTotalMass01());

	if(NeedsUpdate(Inventory))
	{
		ListView->SetListItems(UItemFunctionLibrary::ToHandles(Inventory));
	}
}

bool UInfoCargoTab::NeedsUpdate(const UInventory* Inventory) const
{
	TSet<UItem*> Items = TSet(Inventory->GetItems());
	for(UObject* Object : ListView->GetListItems())
	{
		const UItemHandle* Handle = Cast<UItemHandle>(Object);
		if(IsValid(Handle))
		{
			if(!Items.Contains(Handle->Item))
			{
				return true;
			}
			Items.Remove(Handle->Item);
		}
	}
	return !Items.IsEmpty();
}
