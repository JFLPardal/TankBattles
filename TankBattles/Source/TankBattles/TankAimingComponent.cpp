// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTankAimingComponent::AimAt(FVector LocationToAim, int32 LaunchSpeed) const
{
	if (Barrel == nullptr) { return; }
	FVector OutLaunchVelocity(0);

	if (UGameplayStatics::SuggestProjectileVelocity
		(
			this, 
			OutLaunchVelocity, 
			Barrel->GetSocketLocation(BarrelTipSocketName), 
			LocationToAim, 
			LaunchSpeed,
			false
		)
		)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("aiming at %s"), *AimDirection.ToString());
	}
}



// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::SetBarrelReference( UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
	UE_LOG(LogTemp, Warning, TEXT("barrel set at %s"), *Barrel->GetComponentLocation().ToString());
}

