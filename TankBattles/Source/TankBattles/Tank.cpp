// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankMovementComponent.h"
#include "Engine/StaticMeshSocket.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	UE_LOG(LogTemp, Warning, TEXT("DO IT: Tank Constructor"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();		// IMPORTANT: needed for Tank_BP BeginPlay to be called
	UE_LOG(LogTemp, Warning, TEXT("DO IT: Tank Begin Play"));
}

void ATank::AimAt(FVector HitLocation) const
{
	if (TankAimingComponent != nullptr)
	{
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	}
}

void ATank::Fire()
{
	bool bIsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;
	
	if (bIsReloaded && Barrel != nullptr)
	{
		auto ProjectileSpawned = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(BARREL_TIP_NAME),
			Barrel->GetSocketRotation(BARREL_TIP_NAME)
			);
		ProjectileSpawned->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
	if(Barrel == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank.cpp: No Barrel reference")); 
		return;
	}
}

