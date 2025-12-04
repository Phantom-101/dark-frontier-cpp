// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SectorRoot.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DARKFRONTIER_API USectorRoot : public USceneComponent
{
	GENERATED_BODY()

protected:

	virtual void OnChildAttached(USceneComponent* ChildComponent) override;
	
};
