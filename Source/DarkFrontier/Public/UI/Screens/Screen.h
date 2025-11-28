// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Input/CommonUIInputTypes.h"
#include "Screen.generated.h"

class UCommonBoundActionButton;
class UInputAction;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UScreen : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
protected:

	// Binding handles are registered and unregistered on construct and destruct
	// not on activation and deactivation, as that causes a visual artifact where
	// an action button that is clicked will lose its text while the screen is still fading away,
	// presumably because 1) it is immediately deactivated and 2) interacting with it
	// immediately updates its input action widget
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TArray<FUIActionBindingHandle> BindingHandles;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	virtual void NativeOnActivated() override;

	FUIActionBindingHandle Bind(const UInputAction* InputAction, const FSimpleDelegate& OnExecuteAction);

	template <typename UserClass, typename... ParamTypes, typename... VarTypes>
	FUIActionBindingHandle BindFunction(const UInputAction* InputAction, typename TMemFunPtrType<false, UserClass, void(ParamTypes..., std::decay_t<VarTypes>...)>::Type Function, VarTypes&&... Vars)
	{
		return BindByArgs(FBindUIActionArgs(InputAction, FSimpleDelegate::CreateUObject(Cast<UserClass>(this), Function, Vars...)));
	}

	FUIActionBindingHandle BindScreen(const UInputAction* InputAction, const TSubclassOf<UCommonActivatableWidget>& ScreenClass);

	FUIActionBindingHandle BindByArgs(const FBindUIActionArgs& Args);

	virtual void RegisterBindings();

	virtual void UnregisterBindings();

	UCommonActivatableWidget* FloatScreen(const TSubclassOf<UCommonActivatableWidget>& ScreenClass, bool IsGame) const;

	void FloatScreenDiscard(const TSubclassOf<UCommonActivatableWidget> ScreenClass, bool IsGame);
	
};
