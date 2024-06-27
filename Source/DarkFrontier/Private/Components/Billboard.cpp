// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Billboard.h"

UBillboard::UBillboard()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBillboard::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const FQuat CamQuat = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation().Quaternion();
	const FQuat FlipQuat = FRotator(0, 180, 0).Quaternion();
	const FQuat NewQuat = CamQuat * FlipQuat;
	GetOwner()->SetActorRotation(NewQuat);
}
