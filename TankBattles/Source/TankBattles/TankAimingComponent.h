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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKBATTLES_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup") 
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	void AimAt(FVector LocationToAim);
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State") EFiringState FiringState = EFiringState::Locked;
private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	const FName BarrelTipSocketName = "BarrelTip"; // socket name defined in the barrel .fbx 
private:
	// Sets default values for this component's properties
	UTankAimingComponent();
	UPROPERTY(EditDefaultsOnly, Category = "Firing") int32 LaunchSpeed = 4000;

	void MoveTurretAndBarrelTowards(FVector AimDirection);
};
