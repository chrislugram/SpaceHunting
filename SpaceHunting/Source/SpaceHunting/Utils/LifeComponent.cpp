// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceHunting.h"
#include "LifeComponent.h"

#pragma region CONSTRUCTOR
// Sets default values for this component's properties
ULifeComponent::ULifeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
}
#pragma endregion

#pragma region ENGINE
// Called when the game starts
void ULifeComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentLife = 1;
}

// Called every frame
void ULifeComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}
#pragma endregion

#pragma region LIFE
void ULifeComponent::ApplyDamage(float Damage) 
{
	CurrentLife += (Damage / InitLife);

	if (CurrentLife < 0)
	{
		DiedDelegate.Broadcast();
	}
}
#pragma endregion

