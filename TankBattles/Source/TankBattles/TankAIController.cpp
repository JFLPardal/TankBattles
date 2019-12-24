// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ThisTank = GetPawn(); // TODO delete after refactoring Fire() in Tank.h

	if (!ensure(PlayerTank && ThisTank)) { return; }
	
	MoveToActor(PlayerTank, StoppingDistance);
	//ThisTank->AimAt(PlayerTank->GetActorLocation());
	auto ThisTankAimingComponent = ThisTank->FindComponentByClass<UTankAimingComponent>();
	ThisTankAimingComponent->AimAt(PlayerTank->GetActorLocation());
	//ThisTank->Fire(); // TODO refactor fire() to a sutable class
}




