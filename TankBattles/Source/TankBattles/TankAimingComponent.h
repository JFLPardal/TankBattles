// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8 
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKBATTLES_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable, Category = "Setup") 
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector LocationToAim);

	UFUNCTION(BlueprintCallable) 
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State") EFiringState FiringState = EFiringState::Reloading;
private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, Category = "Firing") int32 LaunchSpeed = 4000;

	const FName BARREL_TIP_SOCKET_NAME = "BarrelTip"; // socket name defined in the barrel .fbx 

	double LastFireTime = 2; // equal to ReloadTimeInSeconds to make sure the player can fire as soon as the game starts
	UPROPERTY(EditDefaultsOnly, Category = "Firing") float ReloadTimeInSeconds = 2;
	UPROPERTY(EditAnywhere, Category = "Firing") TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

private:
	virtual void BeginPlay() override;
	UTankAimingComponent();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
	void MoveTurretAndBarrelTowards(FVector AimDirection);
	bool IsBarrelMoving();
};
