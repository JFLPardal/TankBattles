// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKBATTLES_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetPawn(APawn* InPawn) override;
protected:
	UPROPERTY(EditAnywhere) float StoppingDistance = 8000; // distance to the player before stopping the chase in cms
private:
	UFUNCTION()
	void OnPossessedTankDeath();
};
