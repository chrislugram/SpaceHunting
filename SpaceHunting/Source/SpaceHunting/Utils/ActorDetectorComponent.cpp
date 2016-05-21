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
#pragma endregion