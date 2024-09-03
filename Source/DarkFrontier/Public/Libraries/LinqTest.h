// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LinqTest.generated.h"

UCLASS()
class DARKFRONTIER_API UBase : public UObject
{
	GENERATED_BODY()
};

UCLASS()
class DARKFRONTIER_API UDerived : public UBase
{
	GENERATED_BODY()
};

UCLASS()
class DARKFRONTIER_API UValue : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY()
	int32 Value = 0;

	static UValue* New(int32 InValue);
	
};

template <typename T>
bool ArraysEqual(TArray<T> A, TArray<T> B)
{
	if(A.Num() != B.Num())
	{
		return false;
	}

	for(int Index = 0; Index < A.Num(); ++Index)
	{
		if(A[Index] != B[Index])
		{
			return false;
		}
	}

	return true;
}
