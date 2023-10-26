#include "Structures/StructurePartAuthoring.h"

#include "Structures/Structure.h"
#include "Structures/StructurePart.h"
#include "Structures/StructurePartSlot.h"

UStructurePartAuthoring::UStructurePartAuthoring()
{
}

void UStructurePartAuthoring::BeginPlay()
{
	Super::BeginPlay();

	GetAuthoredPart();
}

AStructurePart* UStructurePartAuthoring::GetAuthoredPart()
{
	if(AuthoredPart == nullptr)
	{
		AuthoredPart = GetWorld()->SpawnActor<AStructurePart>(PartClass);
		
		if(TargetPart == nullptr)
		{
			Cast<AStructure>(GetOwner())->InitRootPart(AuthoredPart);
		}
		else
		{
			AuthoredPart->GetPartSlotByName(UseSlot)->Attach(TargetPart->GetAuthoredPart()->GetPartSlotByName(TargetSlot));
		}

		DestroyComponent();
	}

	return AuthoredPart;
}
