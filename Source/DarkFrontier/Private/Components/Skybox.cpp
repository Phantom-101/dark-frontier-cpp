// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Skybox.h"

USkybox::USkybox()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USkybox::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetOwner()->SetActorLocation(GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation());
}
