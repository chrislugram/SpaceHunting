// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceHunting.h"
#include "Droid.h"
#include "MothershipEnemy.h"

#pragma region CONSTRUCTOR
AMothershipEnemy::AMothershipEnemy() : AEnemy() {}
#pragma endregion

#pragma region ENGINE
void AMothershipEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	// Access to all SpawnComponents
	SpawnComponent = FindComponentByClass<USpawnComponent>();
	if (SpawnComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MothershipEnemy: SpawnComponent not found"));
	}
	else 
	{
		SpawnComponent->SpawnElementDisabled.AddDynamic(this, &AMothershipEnemy::DroidDestroyed);
	}
		

	// Setup the rotation timer
	GetWorldTimerManager().SetTimer(RotationTimer, this, &AMothershipEnemy::UpdateRotation, TimeToChangeRotation, true);

	// Setup the droid generation timer
	GetWorldTimerManager().SetTimer(DroidGenerationTimer, this, &AMothershipEnemy::CheckDroidGeneration, TimeToCreateDroid, true);

	// Setup initial rotation
	CurrentRotation = GetActorRotation();

	// Setup life
	LifeComponent->ResetLife();
}

void AMothershipEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Generate Energy
	CurrentEnergy += DeltaSeconds*EnergySpeedGeneration;

	// Change rotation if it is necessary
	FRotator ActorRotator = GetActorRotation();
	ActorRotator = FMath::RInterpTo(ActorRotator, ActorRotator + CurrentRotation, DeltaSeconds, RotationSpeed*DeltaSeconds);
	SetActorRotation(ActorRotator);

	// Movement
	FVector ActorForward = GetActorForwardVector();
	SetActorLocation(GetActorLocation() + (ActorForward * ForwardSpeed * DeltaSeconds));
	//DrawDebugLine( GetWorld(), GetActorLocation(), GetActorLocation() + (ActorForward * ForwardSpeed), FColor(255, 0, 0), false, 10, 0, 12.333 );
}
#pragma endregion

#pragma region MOTHERSHIP_ENEMY
void AMothershipEnemy::Died()
{
	//UE_LOG(LogTemp, Warning, TEXT("MOTHERSHIP Muere!!!"));
}

void AMothershipEnemy::LifeChanged(float Life)
{
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetControlledPawn();

	if (PlayerPawn != nullptr)
	{
		for (size_t i = 0; i < DroidsReady.Num(); i++)
		{
			DroidsReady[i]->OnActorDetected(PlayerPawn);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PawnPlayer not found"));
	}
}

void AMothershipEnemy::DroidDestroyed(AActor* ActorDisabled)
{
	//UE_LOG(LogTemp, Warning, TEXT("Enemy destroyed!!! %s"), *(ActorDisabled->GetName()));
	ADroid* DroidDisabled = Cast<ADroid>(ActorDisabled);
	DroidsReady.Remove(DroidDisabled);
}

void AMothershipEnemy::UpdateRotation()
{
	CurrentRotation.Roll = 0;
	CurrentRotation.Pitch = FMath::RandRange(-90, 90);
	CurrentRotation.Yaw = FMath::RandRange(-90, 90);
	//UE_LOG(LogTemp, Warning, TEXT("UPDATE ROTATION: %f, %f, %f"), CurrentRotation.Roll, CurrentRotation.Pitch, CurrentRotation.Yaw);
}

void AMothershipEnemy::CheckDroidGeneration()
{
	if (DroidsReady.Num() < MaxDroids)
	{
		// Generate new droid
		AActor* ActorSpawned = SpawnComponent->SpawnActor();
		ADroid* DroidSpawned = Cast<ADroid>(ActorSpawned);
		DroidSpawned->SetMothershipActor(this);

		// Adding droid to list
		DroidsReady.Add(DroidSpawned);
	}
}
#pragma endregion