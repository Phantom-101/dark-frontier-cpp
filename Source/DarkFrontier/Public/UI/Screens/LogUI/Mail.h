// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Timestamp.h"
#include "UObject/Object.h"
#include "Mail.generated.h"

class AFaction;

/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew)
class DARKFRONTIER_API UMail : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Subject;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Body;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<AFaction> Sender;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTimestamp Timestamp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsRead = false;
	
	static UMail* NewMail(AFaction* InSender, const FText& InSubject, const FText& InBody);
	
};
