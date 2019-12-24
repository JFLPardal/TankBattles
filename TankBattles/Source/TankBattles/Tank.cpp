// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/StaticMeshSocket.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();		// IMPORTANT: needed for Tank_BP BeginPlay to be called
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

void ATank::AimAt(FVector HitLocation) const
{
	if (ensure(TankAimingComponent != nullptr))
	{
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	}
}

void ATank::Fire()
{
	if(ensure(Barrel != nullptr))
	{
		bool bIsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;
	
		if (bIsReloaded)
		{
			auto ProjectileSpawned = GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(BARREL_TIP_NAME),
				Barrel->GetSocketRotation(BARREL_TIP_NAME)
				);
			ProjectileSpawned->LaunchProjectile(LaunchSpeed);
			LastFireTime = GetWorld()->GetTimeSeconds();
		}
	}
}

