// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent != nullptr))
	{
		FoundAimingComponent(AimingComponent);
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
	if (!GetPawn()) { return; } // if not possessing the thank, f.e. if the player dies
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	FVector HitLocation(-1);
	if (GetSightRayHitLocation(HitLocation))
	{
		// tell controlled tank to aim at this point
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// find crosshair position on the screen
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D CrosshairScreenLocation(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// de-project the screen position of the crosshair to world direction
	FVector LookDirection;
	if (GetLookDirection(CrosshairScreenLocation, LookDirection))
	{
		// line trace along that direction and test if something is hit (up to max range)
		GetLookVectorHitLocation(LookDirection.GetSafeNormal(), OutHitLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D CrosshairScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation;	// just because deproject needs it, this is not used
	return DeprojectScreenPositionToWorld(CrosshairScreenLocation.X, CrosshairScreenLocation.Y, WorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector& LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceRange;
		
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult, 
			StartLocation, 
			EndLocation, 
			ECollisionChannel::ECC_Visibility)
		)
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false;	// line hit nothing
}
