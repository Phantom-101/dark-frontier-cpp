// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "LogUniverseMapSector.generated.h"

class ULogUniverseMapConnection;
class UCanvasPanel;
class ULogUniverseMapTab;
class UCommonButtonBase;
class ASector;
class UCommonTextBlock;
class UImage;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API ULogUniverseMapSector : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCanvasPanel> Canvas;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> SelectButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> SectorImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> NameText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> SelectionImage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<ULogUniverseMapConnection> ConnectionClass;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<ULogUniverseMapTab> Tab;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<ASector> Sector;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TMap<TObjectPtr<ASector>, TObjectPtr<ULogUniverseMapConnection>> Connections;

	virtual void NativeConstruct() override;

public:

	void Init(ULogUniverseMapTab* InTab, ASector* InSector);

protected:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	void HandleSelect() const;
	
};
