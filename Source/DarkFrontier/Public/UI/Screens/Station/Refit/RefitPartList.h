// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Screens/Screen.h"
#include "RefitPartList.generated.h"

class UListView;
class AStructurePart;

/**
 * 
 */
UCLASS(Abstract)
class DARKFRONTIER_API URefitPartList : public UScreen {
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UListView> ListView;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FGameplayTag Tag;

public:

	UFUNCTION(BlueprintCallable)
	void Populate(TArray<TSubclassOf<AStructurePart>> Parts) const;
	
};
