// Fill out your copyright notice in the Description page of Project Settings.

#include "Libraries/AssetBlueprintFunctionLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "UObject/SavePackage.h"

UPackage* UAssetBlueprintFunctionLibrary::GetPackage(const FString PackageName)
{
	UPackage* Package = CreatePackage(*PackageName);
	Package->FullyLoad();
	return Package;
}

UPackage* UAssetBlueprintFunctionLibrary::GetAssetPackage(UObject* Asset)
{
	return Asset->GetPackage();
}

// Includes both the path to the package and the short name of the package itself
FString UAssetBlueprintFunctionLibrary::GetPackageFullName(UPackage* Package)
{
	return Package->GetName();
}

// Does not include the short name of the package itself
FString UAssetBlueprintFunctionLibrary::GetPackagePath(UPackage* Package)
{
	return FPackageName::GetLongPackagePath(GetPackageFullName(Package));
}

// This is equivalent to getting the package's short name
FString UAssetBlueprintFunctionLibrary::GetPackageName(UPackage* Package)
{
	return FPackageName::GetLongPackageAssetName(GetPackageFullName(Package));
}

FString UAssetBlueprintFunctionLibrary::GetAssetFullName(UPackage* Package)
{
	const FString FullName = GetPackageFullName(Package);

	if(Package->ContainsMap())
	{
		return FPackageName::LongPackageNameToFilename(FullName, FPackageName::GetMapPackageExtension());
	}
	
	return FPackageName::LongPackageNameToFilename(FullName, FPackageName::GetAssetPackageExtension());
}

bool UAssetBlueprintFunctionLibrary::NewAsset(UPackage* Package, UObject* Asset)
{
	(void)Package->MarkPackageDirty();
	FAssetRegistryModule::AssetCreated(Asset);

	const FString PackageFileName = GetAssetFullName(Package);
	
	FSavePackageArgs Args;
	Args.TopLevelFlags = RF_Public | RF_Standalone;
	Args.SaveFlags = SAVE_NoError;
	
	return UPackage::SavePackage(Package, Asset, *PackageFileName, Args);
}
