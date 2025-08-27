// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Selector.generated.h"

class ITargetable;
class UCommonButtonBase;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API USelector : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> SelectButton;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	TScriptInterface<ITargetable> Target;

	virtual void NativeConstruct() override;

public:

	virtual void Init(const TScriptInterface<ITargetable>& InTarget);

	virtual void UpdateSelector(const FGeometry& CanvasGeometry);

private:

	void Select() const;
	
};
