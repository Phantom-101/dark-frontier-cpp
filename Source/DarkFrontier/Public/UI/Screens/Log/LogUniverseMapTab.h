// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "LogUniverseMapTab.generated.h"

class ASector;
class ULogUniverseMapSector;
class UCanvasPanel;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ULogUniverseMapTab : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCanvasPanel> SectorCanvas;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<ULogUniverseMapSector> SectorClass;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<ASector> Selected;

	virtual void NativeConstruct() override;

public:

	ASector* GetSelected() const;

	void SetSelected(ASector* InSelected);
	
};
