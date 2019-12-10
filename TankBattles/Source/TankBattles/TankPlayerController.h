// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class TANKBATTLES_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	void AimTowardsCrosshair();
	ATank* GetControlledTank() const;
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D CrosshairScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(const FVector& LookDirection, FVector& OutHitLocation) const;

private:
	UPROPERTY(EditDefaultsOnly) float CrosshairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly) float CrosshairYLocation = 0.3333f;
	UPROPERTY(EditDefaultsOnly) int32 LineTraceRange = 1000000; // 100km
};
