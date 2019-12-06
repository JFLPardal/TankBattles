// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(FVector LocationToAim, int32 LaunchSpeed)
{
	if (Barrel == nullptr || Turret == nullptr) 
	{
		UE_LOG(LogTemp, Error, TEXT("TAnkAimingComponent: Barrel or Turret reference not set in BP"));
		return; 
	}
	FVector OutLaunchVelocity(0);
	bool bHasAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		Barrel->GetSocketLocation(BarrelTipSocketName),
		LocationToAim,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHasAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		// move turret
		MoveTurretAndBarrelTowards(AimDirection);
		UE_LOG(LogTemp, Warning, TEXT("aiming at %s"), *AimDirection.ToString());
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("not aiming"));
	}
}

void UTankAimingComponent::MoveTurretAndBarrelTowards(FVector AimDirection)
{
	// calculate difference between  current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimDirectionAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimDirectionAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

