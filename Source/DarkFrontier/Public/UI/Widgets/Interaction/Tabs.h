// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Tabs.generated.h"

class UListView;
class UCommonActivatableWidgetStack;
class UCommonActivatableWidget;
class UTabEntry;
class UWidgetSwitcher;

UCLASS(DefaultToInstanced, EditInlineNew)
class DARKFRONTIER_API UTab : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UCommonActivatableWidget> WidgetClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText Name;

	bool IsValid() const;
	
};

DECLARE_MULTICAST_DELEGATE_OneParam(FTabChanged, UCommonActivatableWidget*)

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API UTabs : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListView> ListView;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> TabStack;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TObjectPtr<UTab>> Tabs;

public:

	FTabChanged OnTabChanged;

protected:

	virtual void NativeConstruct() override;

public:

	UTab* GetTab() const;

	UCommonActivatableWidget* GetTabWidget() const;

private:

	void HandleTabSelected(UObject* Tab) const;

	void HandleWidgetChanged(UCommonActivatableWidget* Widget) const;
	
};
