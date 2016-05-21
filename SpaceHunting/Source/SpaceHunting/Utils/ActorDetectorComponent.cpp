// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceHunting.h"
#include "ActorDetectorComponent.h"

#pragma region CONSTRUCTORS
// Sets default values for this component's properties
UActorDetectorComponent::UActorDetectorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}
#pragma endregion

#pragma region ENGINE
// Called when the game starts
void UActorDetectorComponent::BeginPlay()
{
	Super::BeginPlay();	

	// Setup the rotation timer
	GetOwner()->GetWorldTimerManager().SetTimer(DetectorTimer, this, &UActorDetectorComponent::RunDetection, TimeBetweenDetections, true);
}

// Called every frame
void UActorDetectorComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}
#pragma endregion

#pragma region ACTOR_DETECTOR_COMPONENT
void UActorDetectorComponent::SetSphereComponent(USphereComponent* SphereComponent)
{
	SphereDetector = SphereComponent;
	SphereDetector->SetSphereRadius(MaxDistanceDetection);
}

void UActorDetectorComponent::RunDetection()
{
	TArray<AActor*> OverlappingActors;
	GetOwner()->GetOverlappingActors(OverlappingActors);

	if (OverlappingActors.Num() > 0)
	{
		for (size_t i = 0; i < OverlappingActors.Num(); i++)
		{
			if (OverlappingActors[i]->ActorHasTag(TagToDetect))
			{
				// Get directions
				FVector OwnerDirection = GetOwner()->GetActorForwardVector();
				FVector ActorDirection = OverlappingActors[i]->GetActorLocation() - GetOwner()->GetActorLocation();

				// Normalize vectors
				OwnerDirection.Normalize();
				ActorDirection.Normalize();

				// Calculate angle
				float AngleFromForward = FMath::RadiansToDegrees(acosf(FVector::DotProduct(OwnerDirection, ActorDirection)));
				if (AngleFromForward < MaxAngleDetection)
				{
					//UE_LOG(LogTemp, Warning, TEXT("Lanzo Broadcast"));
					ActorDetected.Broadcast(OverlappingActors[i]);
				}
				//UE_LOG(LogTemp, Warning, TEXT("Tiene tag Name: %s y angulo %f, max %f"), *(OverlappingActors[i]->GetName()), AngleFromForward, MaxAngleDetection);
			}
		}
	}
}
#pragma endregion