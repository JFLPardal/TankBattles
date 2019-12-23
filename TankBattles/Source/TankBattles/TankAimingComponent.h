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
	void AimAt(FVector LocationToAim, int32 LaunchSpeed);
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State") EFiringState FiringState = EFiringState::Aiming;
private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	const FName BarrelTipSocketName = "BarrelTip"; // socket name defined in the barrel .fbx 
private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	void MoveTurretAndBarrelTowards(FVector AimDirection);
};
