// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	auto SlippageSpeed = FVector::DotProduct( GetRightVector(), GetComponentVelocity());
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	auto TankRoot = Cast<UStaticMeshComponent> (GetOwner()->GetRootComponent());	/// needed to the the tank's mass 
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;		/// division is made because the tank has 2 tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	Throttle = FMath::Clamp<float>(Throttle, -1, 1);

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); // cast needed to use ApplyForceAtLocation(), see Window > Developer Tools > Class Viewer
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("HITTING"));
}
