// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureLayoutData.h"
#include "Components/ActorComponent.h"
#include "StructureAuthoring.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKFRONTIER_API UStructureAuthoring : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FStructureLayoutData LayoutData;

public:

	FStructureLayoutData GetLayoutData() const;

};
