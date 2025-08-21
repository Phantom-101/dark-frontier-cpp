// Fill out your copyright notice in the Description page of Project Settings.

#include "Libraries/TextureFunctionLibrary.h"
#include "Libraries/AssetFunctionLibrary.h"

void UTextureFunctionLibrary::SaveMipTexture(UTexture2D* Source, const int32 MipFactorX, const int32 MipFactorY)
{
	UPackage* SourcePackage = Source->GetPackage();
	const FString SourceFullName = UAssetFunctionLibrary::GetPackageFullName(SourcePackage);
	const FString SourceName = UAssetFunctionLibrary::GetPackageName(SourcePackage);
	
	const FString DestFullName = FString::Printf(TEXT("%s_Mip"), *SourceFullName);
	const FString DestName = FString::Printf(TEXT("%s_Mip"), *SourceName);

	UPackage* DestPackage = UAssetFunctionLibrary::GetPackage(DestFullName);
	UTexture2D* Dest = NewObject<UTexture2D>(DestPackage, *DestName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
	Dest->AddToRoot();

	InitMipTexture(Dest, Source, MipFactorX, MipFactorY);

	UAssetFunctionLibrary::NewAsset(DestPackage, Dest);
}

// Use int32 instead of uint32 as parameter type as only int32 is supported by blueprints
void UTextureFunctionLibrary::InitMipTexture(UTexture2D* Dest, UTexture2D* Source, const int32 MipFactorX, const int32 MipFactorY)
{
	// Get texture sizes
	const uint32 SourceSizeX = Source->GetSizeX();
	const uint32 SourceSizeY = Source->GetSizeY();
	const uint32 DestSizeX = SourceSizeX / MipFactorX;
	const uint32 DestSizeY = SourceSizeY / MipFactorY;

	// Initialize platform data
	FTexturePlatformData* PlatformData = new FTexturePlatformData();
	Dest->SetPlatformData(PlatformData);
	PlatformData->SizeX = DestSizeX;
	PlatformData->SizeY = DestSizeY;
	PlatformData->SetNumSlices(1);
	PlatformData->PixelFormat = PF_B8G8R8A8;

	// Get pointers to working arrays
	const uint8* SourceData = Source->Source.LockMipReadOnly(0);
	uint8* DestData = new uint8[DestSizeX * DestSizeY * 4];

	// Downsample
	for(uint32 Y = 0; Y < DestSizeY; Y++)
	{
		for(uint32 X = 0; X < DestSizeX; X++)
		{
			uint32 Accumulated0 = 0;
			uint32 Accumulated1 = 0;
			uint32 Accumulated2 = 0;
			uint32 Accumulated3 = 0;
			
			const uint32 MinSourceY = (Y + 0) * MipFactorY;
			const uint32 MaxSourceY = (Y + 1) * MipFactorY;
			for(uint32 SourceY = MinSourceY; SourceY < MaxSourceY; SourceY++)
			{
				const uint32 MinSourceX = (X + 0) * MipFactorX;
				const uint32 MaxSourceX = (X + 1) * MipFactorX;
				for(uint32 SourceX = MinSourceX; SourceX < MaxSourceX; SourceX++)
				{
					const uint32 SourceIndex = (SourceY * SourceSizeX + SourceX) * 4;
					Accumulated0 += SourceData[SourceIndex + 0];
					Accumulated1 += SourceData[SourceIndex + 1];
					Accumulated2 += SourceData[SourceIndex + 2];
					Accumulated3 += SourceData[SourceIndex + 3];
				}
			}

			const uint32 DestIndex = (Y * DestSizeX + X) * 4;
			const uint32 SourceSize = MipFactorX * MipFactorY;
			DestData[DestIndex + 0] = Accumulated0 / SourceSize;
			DestData[DestIndex + 1] = Accumulated1 / SourceSize;
			DestData[DestIndex + 2] = Accumulated2 / SourceSize;
			DestData[DestIndex + 3] = Accumulated3 / SourceSize;
		}
	}

	// Unlock the source texture as it will not be used later
	Source->Source.UnlockMip(0);

	// Expand texels into neighbors

	/*
	static constexpr uint32 Weights[3][3] =
	{
		{ 1, 255, 1 },
		{ 255, 0, 255 },
		{ 1, 255, 1 },
	};
	
	for(uint32 Y = 0; Y < DestSizeY; Y++)
	{
		for(uint32 X = 0; X < DestSizeX; X++)
		{
			uint32 Accumulated0 = 0;
			uint32 Accumulated1 = 0;
			uint32 Accumulated2 = 0;
			uint32 Accumulated3 = 0;
			uint32 AccumulatedWeight = 0;
			
			const uint32 MinSourceY = FMath::Max(Y - 1, 0U);
			const uint32 MaxSourceY = FMath::Min(Y + 1, SourceSizeY - 1);
			for(uint32 SourceY = MinSourceY; SourceY < MaxSourceY; SourceY++)
			{
				const uint32 MinSourceX = FMath::Max(X - 1, 0U);
				const uint32 MaxSourceX = FMath::Min(X + 1, SourceSizeX - 1);
				for(uint32 SourceX = MinSourceX; SourceX < MaxSourceX; SourceX++)
				{
					const uint32 SourceIndex = (SourceY * SourceSizeX + SourceX) * 4;
					const uint32 WeightX = SourceX - X + 1;
					const uint32 WeightY = SourceY - Y + 1;
					const uint32 Weight = Weights[WeightY][WeightX];
					Accumulated0 += SourceData[SourceIndex + 0] * Weight;
					Accumulated1 += SourceData[SourceIndex + 1] * Weight;
					Accumulated2 += SourceData[SourceIndex + 2] * Weight;
					Accumulated3 += SourceData[SourceIndex + 3] * Weight;
					AccumulatedWeight += Weight;
				}
			}

			if(AccumulatedWeight != 0)
			{
				const uint32 DestIndex = (Y * DestSizeX + X) * 4;
				DestData[DestIndex + 0] = FMath::Clamp(static_cast<uint32>(DestData[DestIndex + 0]) + Accumulated0 / AccumulatedWeight, 0, 255);
				DestData[DestIndex + 1] = FMath::Clamp(static_cast<uint32>(DestData[DestIndex + 1]) + Accumulated1 / AccumulatedWeight, 0, 255);
				DestData[DestIndex + 2] = FMath::Clamp(static_cast<uint32>(DestData[DestIndex + 2]) + Accumulated2 / AccumulatedWeight, 0, 255);
				DestData[DestIndex + 3] = FMath::Clamp(static_cast<uint32>(DestData[DestIndex + 3]) + Accumulated3 / AccumulatedWeight, 0, 255);
			}
		}
	}
	*/

	// Initialize mip texture
	FTexture2DMipMap* Mip = new FTexture2DMipMap();
	PlatformData->Mips.Add(Mip);
	Mip->SizeX = DestSizeX;
	Mip->SizeY = DestSizeY;

	// Transfer working array into mip texture data
	Mip->BulkData.Lock(LOCK_READ_WRITE);
	uint8* TextureData = Mip->BulkData.Realloc(DestSizeX * DestSizeY * 4);
	FMemory::Memcpy(TextureData, DestData, sizeof(uint8) * DestSizeX * DestSizeY * 4);
	Mip->BulkData.Unlock();

	// Initialize texture source and cleanup
	Dest->Source.Init(DestSizeX, DestSizeY, 1, 1, TSF_BGRA8, DestData);
	delete DestData;

	Dest->UpdateResource();
}
