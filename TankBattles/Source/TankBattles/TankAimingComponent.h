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
	// Sets default values for this component's properties
	UTankAimingComponent();
	
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UTankTurret* TurretToSet);

	void AimAt(FVector LocationToAim, int32 LaunchSpeed);
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State") EFiringState FiringState = EFiringState::Reloading;
private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;


	const FName BarrelTipSocketName = "BarrelTip"; // socket name defined in the barrel .fbx 
private:
	void MoveTurretAndBarrelTowards(FVector AimDirection);
};
