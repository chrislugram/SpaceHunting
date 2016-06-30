// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "Blueprint/UserWidget.h"
#include "SpaceHuntingGameMode.generated.h"

class ASpaceship;
class AMothershipEnemy;

/**
 * 
 */
UCLASS()
class SPACEHUNTING_API ASpaceHuntingGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Logic")
	virtual void InitializeGame();

	UFUNCTION(BlueprintCallable, Category = "Logic")
	bool IsGameOver();
	
	UFUNCTION(BlueprintCallable, Category = "Logic")
	bool IsWinGame();
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	float UI_GetMothershipLife();

	UFUNCTION(BlueprintCallable, Category = "UI")
	float UI_GetSpaceshipLife();

	

protected:
	class ASpaceship* Spaceship;

	class AMothershipEnemy* Mothership;
};
