// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AssetBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UAssetBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static UPackage* GetPackage(FString PackageName);

	UFUNCTION(BlueprintCallable)
	static UPackage* GetAssetPackage(UObject* Asset);

	UFUNCTION(BlueprintCallable)
	static FString GetPackageFullName(UPackage* Package);

	UFUNCTION(BlueprintCallable)
	static FString GetPackagePath(UPackage* Package);

	UFUNCTION(BlueprintCallable)
	static FString GetPackageName(UPackage* Package);

	UFUNCTION(BlueprintCallable)
	static FString GetAssetFullName(UPackage* Package);

	UFUNCTION(BlueprintCallable)
	static bool NewAsset(UPackage* Package, UObject* Asset);
	
};
