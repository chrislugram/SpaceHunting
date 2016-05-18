// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceHunting.h"
#include "SpawnComponent.h"

#pragma region CONSTRUCTOR
// Sets default values for this component's properties
USpawnComponent::USpawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}
#pragma endregion

#pragma region ENGINE
// Called when the game starts
void USpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	// Setup the spawn components
	UObject * object = GetOwner()->GetDefaultSubobjectByName(SpawnPointName);
	SpawnPoint = Cast<USceneComponent>(object);
	if (SpawnPoint == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PointSpawn NOT FOUND"));
	}
	else
	{
		SpawnPoint->bAbsoluteRotation = true;
	}

	ReloadSpawn = true;
	GetOwner()->GetWorldTimerManager().SetTimer(SpawnTimer, this, &USpawnComponent::FinishReloadTime, ReloadTime, true);
	GetOwner()->GetWorldTimerManager().PauseTimer(SpawnTimer);
	DisabledSpawnElements.Init(0);
}

// Called every frame
void USpawnComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}
#pragma endregion

#pragma region SPAWN_COMPONENT
// Called when reload time finished
void USpawnComponent::FinishReloadTime()
{
	ReloadSpawn = true;
	GetOwner()->GetWorldTimerManager().UnPauseTimer(SpawnTimer);
}

// Called to store a spawn element
void USpawnComponent::AddDisabledSpawnElement(USpawnElement * SpawnElement)
{
	DisabledSpawnElements.Add(SpawnElement);
}

// Called to spawn object in world
void USpawnComponent::SpawnActor()
{
	// If yet reload and we have set something to spawn
	if (ReloadSpawn && (SpawnBP != nullptr))
	{
		// Activate reload time
		ReloadSpawn = false;
		GetOwner()->GetWorldTimerManager().UnPauseTimer(SpawnTimer);

		// Check for valid world
		UWorld* const OurWorld = GetWorld();
		if (OurWorld != nullptr)
		{
			AActor* ActorSpawned = nullptr;

			// Get location to spawn at
			FVector SpawnLocation = GetSpawnPoint();

			// Check if we have any spawn element disable
			if (DisabledSpawnElements.Num() == 0)
			{
				// Set the spawn parameters
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this->GetOwner();
				SpawnParams.Instigator = this->GetOwner()->Instigator;

				// Create a spawn element
				ActorSpawned = OurWorld->SpawnActor<AActor>(SpawnBP, SpawnLocation, GetOwner()->GetActorRotation(), SpawnParams);
			}
			else
			{
				// Get actor from pool
				ActorSpawned = DisabledSpawnElements[0]->GetOwner();
				DisabledSpawnElements.RemoveAt(0);

				// Recalculate position and direction
				ActorSpawned->SetActorLocation(SpawnLocation);
				ActorSpawned->SetActorRotation(GetOwner()->GetActorRotation());
			}

			// Initialized spawn element
			USpawnElement* SpawnElement = ActorSpawned->FindComponentByClass<USpawnElement>();
			if (SpawnElement != nullptr)
			{
				SpawnElement->InitElement(this);
			}
		}
	}
}

// Return the point where spawn a object
FVector USpawnComponent::GetSpawnPoint() 
{
	return SpawnPoint->GetComponentLocation();
}
#pragma endregion

