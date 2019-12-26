// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ThisTank = GetPawn(); 

	if (!ensure(PlayerTank && ThisTank)) { return; }
	
	MoveToActor(PlayerTank, StoppingDistance);
	auto ThisTankAimingComponent = ThisTank->FindComponentByClass<UTankAimingComponent>();
	ThisTankAimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (ThisTankAimingComponent->GetFiringState() == EFiringState::Locked)
	{
		ThisTankAimingComponent->Fire();
	}
}

// Doing this on BeginPlay might be too early, to avoid racing conditions we do it when ...
void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank> (InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}




