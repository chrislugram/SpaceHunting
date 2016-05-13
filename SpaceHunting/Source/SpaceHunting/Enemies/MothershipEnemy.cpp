// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceHunting.h"
#include "MothershipEnemy.h"

#pragma region ENGINE
void AMothershipEnemy::BeginPlay()
{
	Super::BeginPlay();

	// Setup the rotation timer
	GetWorldTimerManager().SetTimer(RotationTimer, this, &AMothershipEnemy::UpdateRotation, TimeToChangeRotation, true);

	// Setup initial rotation
	CurrentRotation = GetActorRotation();
}

void AMothershipEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Generate Energy
	CurrentEnergy += DeltaSeconds*EnergySpeedGeneration;

	// Change rotation if it is necessary
	FRotator ActorRotator = GetActorRotation();
	//UE_LOG(LogTemp, Warning, TEXT("Prev Rotation: %f, %f, %f"), ActorRotator.Pitch, ActorRotator.Yaw, ActorRotator.Yaw);
	//UE_LOG(LogTemp, Warning, TEXT("Prev Current: %f, %f, %f"), CurrentRotation.Pitch, CurrentRotation.Yaw, CurrentRotation.Roll);
	ActorRotator = FMath::RInterpTo(ActorRotator, ActorRotator + CurrentRotation, DeltaSeconds, RotationSpeed*DeltaSeconds);
	//UE_LOG(LogTemp, Warning, TEXT("Post Rotation: %f, %f, %f"), ActorRotator.Pitch, ActorRotator.Yaw, ActorRotator.Yaw);
	SetActorRotation(ActorRotator);

	// Movement
	FVector ActorForward = GetActorForwardVector();
	SetActorLocation(GetActorLocation() + (ActorForward * ForwardSpeed * DeltaSeconds));
	DrawDebugLine(
		GetWorld(),
		GetActorLocation(),
		GetActorLocation() + (ActorForward * ForwardSpeed),
		FColor(255, 0, 0),
		false, 10, 0,
		12.333
		);
}
#pragma endregion

#pragma region MOTHERSHIP_ENEMY
void AMothershipEnemy::UpdateRotation()
{
	CurrentRotation.Roll = 0;
	CurrentRotation.Pitch = FMath::RandRange(-90, 90);
	CurrentRotation.Yaw = FMath::RandRange(-90, 90);
	UE_LOG(LogTemp, Warning, TEXT("UPDATE ROTATION: %f, %f, %f"), CurrentRotation.Roll, CurrentRotation.Pitch, CurrentRotation.Yaw);
}
#pragma endregion