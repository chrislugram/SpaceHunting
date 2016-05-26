// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "Enemies/MothershipEnemy.h"
#include "Spaceship.h"
#include "Blueprint/UserWidget.h"
#include "SpaceHuntingGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPACEHUNTING_API ASpaceHuntingGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "UI")
	float UI_GetMothershipLife();

	UFUNCTION(BlueprintCallable, Category = "UI")
	float UI_GetSpaceshipLife();

protected:
	class ASpaceship* Spaceship;

	class AMothershipEnemy* Mothership;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;
};
