// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceHunting.h"
#include "Droid.h"

#pragma region ENGINE
void ADroid::BeginPlay()
{
	Super::BeginPlay();

	// Setup rotation movement
	RunningTime = 0;
}

void ADroid::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//Rotation
	RunningTime += DeltaSeconds;

	FRotator OffsetRotator = FRotator::ZeroRotator;
	OffsetRotator.Pitch = FMath::Sin(RunningTime) * OffsetAngleRotation;
	OffsetRotator.Yaw = FMath::Sin(RunningTime) * OffsetAngleRotation;

	FRotator ActorRotator = GetActorRotation();
	ActorRotator = FMath::RInterpTo(ActorRotator, (MothershipActor->GetActorRotation() + OffsetRotator), DeltaSeconds, RotationSpeed*DeltaSeconds);
	SetActorRotation(ActorRotator);

	// Movement
	FVector ActorForward = GetActorForwardVector();
	SetActorLocation(GetActorLocation() + (ActorForward * ForwardSpeed * DeltaSeconds));
	DrawDebugLine(
		GetWorld(),
		GetActorLocation(),
		GetActorLocation() + (ActorForward * ForwardSpeed),
		FColor(0, 0, 255),
		false, 10, 0,
		12.333
		);
}
#pragma endregion

#pragma region DROID
void ADroid::SetMothershipActor(AActor* Mothership)
{
	MothershipActor = Mothership;
}
#pragma endregion

