// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceHunting.h"
#include "SpawnComponent.h"
#include "SpawnElement.h"

#pragma region CONSTRUCTOR
// Sets default values for this component's properties
USpawnElement::USpawnElement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
#pragma endregion

#pragma region ENGINE
// Called when the game starts
void USpawnElement::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void USpawnElement::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}
#pragma endregion

#pragma region SPAWN_ELEMENT
void USpawnElement::InitElement(USpawnComponent* Spawner)
{
	SpawnerOwner = Spawner;
	EnableElement();
	
	if (DisableTime > 0) 
	{
		GetOwner()->GetWorldTimerManager().SetTimer(EnableTimer, this, &USpawnElement::DisableElement, DisableTime, false);
	}
}

void USpawnElement::DisableElement()
{
	//UE_LOG(LogTemp, Warning, TEXT("DISABLE SPAWN ELEMENT"));
	SpawnerOwner->AddDisabledSpawnElement(this);

	DisabledDelegate.Broadcast();

	GetOwner()->SetActorTickEnabled(false);
	GetOwner()->SetActorEnableCollision(false);
	GetOwner()->SetActorHiddenInGame(true);
}

void USpawnElement::EnableElement()
{
	//UE_LOG(LogTemp, Warning, TEXT("ENABLE SPAWN ELEMENT"));
	GetOwner()->SetActorTickEnabled(true);
	GetOwner()->SetActorEnableCollision(true);
	GetOwner()->SetActorHiddenInGame(false);

	EnabledDelegate.Broadcast();
}
#pragma endregion

