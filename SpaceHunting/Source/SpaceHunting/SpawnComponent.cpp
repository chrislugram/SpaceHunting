// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceHunting.h"
#include "SpawnComponent.h"


// Sets default values for this component's properties
USpawnComponent::USpawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	// Setup the spawn components
	UObject * object = GetOwner()->GetDefaultSubobjectByName(TEXT("SpawnPoint"));
	SpawnPoint = Cast<USceneComponent>(object);
	if (SpawnPoint == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PointSpawn NOT FOUND"));
	}

	ReloadSpawn = true;
	GetOwner()->GetWorldTimerManager().SetTimer(SpawnTimer, this, &USpawnComponent::FinishReloadTime, ReloadTime, true);
	GetOwner()->GetWorldTimerManager().PauseTimer(SpawnTimer);
}


// Called every frame
void USpawnComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void USpawnComponent::FinishReloadTime()
{
	UE_LOG(LogTemp, Warning, TEXT("VUELVO A PODER DISPARAR"));
	ReloadSpawn = true;
	GetOwner()->GetWorldTimerManager().UnPauseTimer(SpawnTimer);
}

// Called to spawn object in world
void USpawnComponent::SpawnActor()
{
	// If yet reload and we have set something to spawn
	if (ReloadSpawn && (SpawnElement != nullptr))
	{
		// Check for valid world
		UWorld* const OurWorld = GetWorld();
		if (OurWorld != nullptr)
		{
			// Check if we have any spawn object inactive
			// if no, set the spawn parameters
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this->GetOwner();
			SpawnParams.Instigator = this->GetOwner()->Instigator;

			// Get location to spawn at
			FVector SpawnLocation = GetSpawnPoint();
			// spawn object
			AActor * const ActorSpawned = OurWorld->SpawnActor<AActor>(SpawnElement, SpawnLocation, FRotator(0, 0, 0), SpawnParams);
			UE_LOG(LogTemp, Warning, TEXT("Create spawn element %s"), *(ActorSpawned->GetName()));
			// if yes, reactivate the first object
				// spawn object

			// Activate reload time
			ReloadSpawn = false;
			GetOwner()->GetWorldTimerManager().UnPauseTimer(SpawnTimer);
		}
	}
}

// Return the point where spawn a object
FVector USpawnComponent::GetSpawnPoint() 
{
	return SpawnPoint->GetComponentLocation();
}

