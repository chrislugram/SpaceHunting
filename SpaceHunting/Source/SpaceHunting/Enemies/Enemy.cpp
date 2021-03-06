// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceHunting.h"
#include "Utils/LifeComponent.h"
#include "Enemy.h"

#pragma region CONSTRUCTOR
// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
#pragma endregion

#pragma region ENGINE
// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	// Setup life
	LifeComponent = FindComponentByClass<ULifeComponent>();
	if (LifeComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Life component NOT FOUND"));
		return;
	}
	LifeComponent->LifeChangeDelegate.AddDynamic(this, &AEnemy::LifeChanged);
	LifeComponent->DiedDelegate.AddDynamic(this, &AEnemy::Died);
}

// Called every frame
void AEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
#pragma endregion

#pragma region ENEMY
void AEnemy::Died()
{
	//UE_LOG(LogTemp, Warning, TEXT("Muere!!!"));
}

void AEnemy::LifeChanged(float Life)
{
	//UE_LOG(LogTemp, Warning, TEXT("Cambia vida!!! %f"), Life);
}
#pragma endregion

