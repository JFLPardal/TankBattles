// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto PlayerTank = Cast<ATank> (GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ThisTank = Cast<ATank>(GetPawn());

	if (PlayerTank != nullptr)
	{
		MoveToActor(PlayerTank, StoppingDistance);
		ThisTank->AimAt(PlayerTank->GetActorLocation());
		ThisTank->Fire();
	}
}




