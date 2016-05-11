// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceHunting.h"
#include "MothershipEnemy.h"

#pragma region ENGINE
void AMothershipEnemy::BeginPlay()
{
	Super::BeginPlay();

	// Setup the rotation timer
	GetWorldTimerManager().SetTimer(RotationTimer, this, &AMothershipEnemy::UpdateRotation, TimeToChangeRotation, true);
}

void AMothershipEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Generate Energy
	CurrentEnergy += DeltaSeconds*EnergySpeedGeneration;

	// Change rotation if it is necessary

	// Movement
	FVector ActorForward = GetActorForwardVector();
	SetActorLocation(GetActorLocation() + (ActorForward * ForwardSpeed * DeltaSeconds));
}
#pragma endregion

#pragma region MOTHERSHIP_ENEMY
void AMothershipEnemy::UpdateRotation()
{
	UE_LOG(LogTemp, Warning, TEXT("UPDATE ROTATION"));
}
#pragma endregion