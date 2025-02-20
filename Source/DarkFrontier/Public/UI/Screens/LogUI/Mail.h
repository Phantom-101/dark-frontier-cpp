// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Mail.generated.h"

class UGameTimestamp;

/**
 * 
 */
UCLASS()
class DARKFRONTIER_API UMail : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Subject;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Body;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UGameTimestamp> Timestamp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsRead = false;
	
};
