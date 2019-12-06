// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), HideCategories = (Physics, Collision)) // hide categories not working
class TANKBATTLES_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	// -1 is max downward speed, +1 is max upwards speed
	void Elevate(float RelativeSpeed);
private:
	UPROPERTY(EditAnywhere, Category = Setup) float MaxDegreesPerSecond = 10;
	UPROPERTY(EditAnywhere, Category = Setup) float MinElevationInDegrees = 0;
	UPROPERTY(EditAnywhere, Category = Setup) float MaxElevationInDegrees = 40;
};
