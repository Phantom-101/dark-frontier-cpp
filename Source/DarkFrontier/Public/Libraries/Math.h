// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Math.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UMath : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static FORCEINLINE float Div(const float A, const float B, const float Fallback)
	{
		return B == 0 ? Fallback : A / B;
	}

	UFUNCTION(BlueprintCallable)
	static FORCEINLINE float DivTo0(const float A, const float B)
	{
		return Div(A, B, 0);
	}

	UFUNCTION(BlueprintCallable)
	static FORCEINLINE float DivTo1(const float A, const float B)
	{
		return Div(A, B, 1);
	}
	
};
