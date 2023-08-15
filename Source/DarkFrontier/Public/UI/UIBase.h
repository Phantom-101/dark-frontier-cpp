// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "CommonUserWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "UIBase.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UUIBase : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> GameStack;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> GameMenuStack;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> MenuStack;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> ModalStack;

public:

	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* PeekGame() const;

	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* PushGame(TSubclassOf<UCommonActivatableWidget> WidgetClass) const;

	template <typename WidgetType = UCommonActivatableWidget>
	WidgetType* PushGame(const TSubclassOf<UCommonActivatableWidget> WidgetClass) const
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, FString::Printf(TEXT("Game stack pushed: %s"), *WidgetClass->GetDisplayNameText().ToString()));
		return GameStack->AddWidget<WidgetType>(WidgetClass);
	}

	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* PeekGameMenu() const;

	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* PushGameMenu(TSubclassOf<UCommonActivatableWidget> WidgetClass) const;
	
	template <typename WidgetType = UCommonActivatableWidget>
	WidgetType* PushGameMenu(const TSubclassOf<UCommonActivatableWidget> WidgetClass) const
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, FString::Printf(TEXT("GameMenu stack pushed: %s"), *WidgetClass->GetDisplayNameText().ToString()));
		return GameMenuStack->AddWidget<WidgetType>(WidgetClass);
	}

	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* PeekMenu() const;

	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* PushMenu(TSubclassOf<UCommonActivatableWidget> WidgetClass) const;
	
	template <typename WidgetType = UCommonActivatableWidget>
	WidgetType* PushMenu(const TSubclassOf<UCommonActivatableWidget> WidgetClass) const
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, FString::Printf(TEXT("Menu stack pushed: %s"), *WidgetClass->GetDisplayNameText().ToString()));
		return MenuStack->AddWidget<WidgetType>(WidgetClass);
	}
	
	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* PeekModal() const;

	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* PushModal(TSubclassOf<UCommonActivatableWidget> WidgetClass) const;
	
	template <typename WidgetType = UCommonActivatableWidget>
	WidgetType* PushModal(const TSubclassOf<UCommonActivatableWidget> WidgetClass) const
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, FString::Printf(TEXT("Modal stack pushed: %s"), *WidgetClass->GetDisplayNameText().ToString()));
		return ModalStack->AddWidget<WidgetType>(WidgetClass);
	}
	
};
