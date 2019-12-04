// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (ControlledTank != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("tank controlled by AI %s"), *ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController can't posses a tank"));
	}

	auto PlayerControlledTank = GetPlayerControlledTank();
	if (PlayerControlledTank == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find Player Controlled tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("tank controlled by player %s"), *PlayerControlledTank->GetName());
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerControlledTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (PlayerPawn == nullptr) { return nullptr;}

	return Cast<ATank>(PlayerPawn);
}


