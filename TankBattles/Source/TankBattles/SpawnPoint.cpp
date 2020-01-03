// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	// using Deferred will delay the spawning until 'FinishSpawningActor', this gives us time to make any additional setup before actually spawning the actor
	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(ActorToSpawnBlueprint, GetComponentTransform());
	if (!SpawnedActor) return;
	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);	
	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
}

void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

