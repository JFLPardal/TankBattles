// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UPhysicsConstraintComponent;

UCLASS()
class TANKBATTLES_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	ASprungWheel();

	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Axle = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* BodyAxleConstraint = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;
private:
	void SetupConstraint();
};
