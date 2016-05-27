// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceHunting.h"
#include "SpaceHuntingGameMode.h"

#pragma region ENGINE
void ASpaceHuntingGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Setup spaceship
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetControlledPawn();
	Spaceship = Cast<ASpaceship>(PlayerPawn);

	if (Spaceship == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("GAME_MODE: Spaceship not found"));

	// Setup Mothership
	for (TActorIterator<AMothershipEnemy> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Mothership = *ActorItr;
		//UE_LOG(LogTemp, Warning, TEXT("GAME_MODE: name: %s"), *(Mothership->GetName()));
	}
}

void ASpaceHuntingGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Check if spaceship dead
	if ((UI_GetSpaceshipLife() <= 0) || (Mothership->GetEnergyGeneratedNormalized() >= 1))
	{
		UE_LOG(LogTemp, Warning, TEXT("GAME OVER"));
	}
	// Check if mothership dead
	else if (UI_GetMothershipLife() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("WIN GAME"));
	}
}
#pragma endregion

#pragma region SPACE_HUNTING_GAME_MODE
float ASpaceHuntingGameMode::UI_GetMothershipLife()
{
	return Mothership->FindComponentByClass<ULifeComponent>()->GetCurrentLife();
}

float ASpaceHuntingGameMode::UI_GetSpaceshipLife()
{
	return Spaceship->FindComponentByClass<ULifeComponent>()->GetCurrentLife();
}
#pragma endregion


