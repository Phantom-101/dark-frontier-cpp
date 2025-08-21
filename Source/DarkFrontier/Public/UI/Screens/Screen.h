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
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TArray<FUIActionBindingHandle> BindingHandles;

	virtual void NativeOnActivated() override;

	virtual void NativeOnDeactivated() override;

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

	void FloatScreen(const TSubclassOf<UCommonActivatableWidget> ScreenClass, bool IsGame);
	
};
