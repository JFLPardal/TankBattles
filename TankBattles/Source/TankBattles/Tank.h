// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//#include "Projectile.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class TANKBATTLES_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet) const;
	/*
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetProjectileReference(AProjectile* ProjectileToSet);*/

	void AimAt(FVector HitLocation) const;
	UFUNCTION(BlueprintCallable) void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankAimingComponent* TankAimingComponent = nullptr;
private:
	UPROPERTY(EditDefaultsOnly, Category = Firing) int32 LaunchSpeed = 4000;
	UPROPERTY(EditAnywhere, Category = Firing) TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Firing) float ReloadTimeInSeconds = 2;

	UTankBarrel* Barrel = nullptr;
	double LastFireTime = 2; // equal to ReloadTimeInSeconds to make sure the player can fire as soon as the game starts

	const FName BARREL_TIP_NAME = "BarrelTip"; // socket name defined on the barrel .fbx for the tip of the barrel
};
