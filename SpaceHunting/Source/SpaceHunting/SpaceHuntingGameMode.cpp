// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceHunting.h"
#include "Enemies/MothershipEnemy.h"
#include "Utils/LifeComponent.h"
#include "Spaceship.h"
#include "SpaceHuntingGameMode.h"

#pragma region SPACE_HUNTING_GAME_MODE
void ASpaceHuntingGameMode::InitializeGame()
{
	// Setup spaceship
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	Spaceship = Cast<ASpaceship>(PlayerPawn);

	if (Spaceship == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("GAME_MODE: Spaceship not found"));

	// Setup Mothership
	for (TActorIterator<AMothershipEnemy> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Mothership = *ActorItr;
		UE_LOG(LogTemp, Warning, TEXT("GAME_MODE: name: %s"), *(Mothership->GetName()));
	}
}

bool ASpaceHuntingGameMode::IsGameOver()
{
	return (((UI_GetSpaceshipLife() <= 0) || (Mothership->GetEnergyGeneratedNormalized() >= 1)));
}

bool ASpaceHuntingGameMode::IsWinGame()
{
	return (UI_GetMothershipLife() <= 0);
}

float ASpaceHuntingGameMode::UI_GetMothershipLife()
{
	return Mothership->FindComponentByClass<ULifeComponent>()->GetCurrentLife();
}

float ASpaceHuntingGameMode::UI_GetSpaceshipLife()
{
	return Spaceship->FindComponentByClass<ULifeComponent>()->GetCurrentLife();
}
#pragma endregion


