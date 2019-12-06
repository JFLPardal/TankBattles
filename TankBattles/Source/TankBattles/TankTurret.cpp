// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	float RotationChange = FMath::Clamp<float>(RelativeSpeed, -1, 1) * GetWorld()->DeltaTimeSeconds * MaxDegreesPerSecond;
	float NewRotation = GetComponentRotation().Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, NewRotation, 0));
}


