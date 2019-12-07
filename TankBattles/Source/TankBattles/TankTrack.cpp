// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "components/PrimitiveComponent.h"

void UTankTrack::SetThrottle(float Throttle)
{
	Throttle = FMath::Clamp<float>(Throttle, -1, 1);

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); // cast needed to use ApplyForceAtLocation(), see Window > Developer Tools > Class Viewer
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

