// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tank tracks
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKBATTLES_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = Setup) void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	
	UFUNCTION(BlueprintCallable, Category = Input) void IntendMoveForward(float Throw);
	// negative Throw will make tank turn to the left
	UFUNCTION(BlueprintCallable, Category = Input) void IntendTurnRight(float Throw);

private:
	UTankTrack* RightTrack = nullptr;
	UTankTrack* LeftTrack = nullptr;
};
