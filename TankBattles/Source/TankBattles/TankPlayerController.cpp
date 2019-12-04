// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();

	if (ControlledTank != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();
}

// Point the tank's turret to where the player's crosshair is
void ATankPlayerController::AimTowardsCrosshair()
{
	if (GetControlledTank() == nullptr) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		// tell controlled tank to aim at this point
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *HitLocation.ToString());
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	// find crosshair position on the screen
	FVector2D CrosshairScreenLocation(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// de-project the screen position of the crosshair to world direction
	// line trace along that direction and test if something is hit (up to max range)
	return true;
}
