// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

class UPrimitiveComponent;
class AActor;

/**
 * TankTrack is used to move the tank and set the maximum drive force
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKBATTLES_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
private:
	UTankTrack();
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult &Hit);
	
	void ApplySidewaysForce();
	void DriveTrack();
private:
	// max force per track in newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 60000000; // Assuming 40T tanks

	float CurrentThrottle = 0;
};
