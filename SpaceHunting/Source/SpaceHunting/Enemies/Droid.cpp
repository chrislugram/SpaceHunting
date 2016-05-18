// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceHunting.h"
#include "Droid.h"

#pragma region ENGINE
void ADroid::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

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

