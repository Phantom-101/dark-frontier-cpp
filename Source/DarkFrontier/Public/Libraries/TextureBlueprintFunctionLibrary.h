// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TextureBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UTextureBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static void SaveMipTexture(UTexture2D* Source, int32 MipFactorX, int32 MipFactorY);

	UFUNCTION(BlueprintCallable)
	static void InitMipTexture(UTexture2D* Dest, UTexture2D* Source, int32 MipFactorX, int32 MipFactorY);
	
};
