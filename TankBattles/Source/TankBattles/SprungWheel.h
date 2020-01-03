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
	UFUNCTION()	
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ApplyForce();
private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Axle = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* BodyAxleConstraint = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;

	float TotalForceMagnitudeThisFrame = 0;
private:
	void SetupConstraint();
};
