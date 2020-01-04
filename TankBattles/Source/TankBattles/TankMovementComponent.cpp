// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "GameFramework/Actor.h"

void UTankMovementComponent::Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	FMath::Clamp<float>(Throw, -1, 1);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) {	return; }
	FMath::Clamp<float>(Throw, -1, 1);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// we are replacing the functionality from the parent class, so no Super:: call
	auto TankForwardNormalized = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto MoveVelocityNormalized = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForwardNormalized, MoveVelocityNormalized);
	auto RightThrow = FVector::CrossProduct(TankForwardNormalized, MoveVelocityNormalized).Z;

	IntendMoveForward(ForwardThrow);
	IntendTurnRight(RightThrow);
}
