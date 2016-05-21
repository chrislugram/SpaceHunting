// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceHunting.h"
#include "Droid.h"

#pragma region CONSTRUCTORS
ADroid::ADroid() : AEnemy() {}
#pragma endregion

#pragma region ENGINE
void ADroid::BeginPlay()
{
	Super::BeginPlay();

	// Setup rotation movement
	RunningTime = 0;

	// Setup detector
	DroidDetector = FindComponentByClass<UActorDetectorComponent>();
	if (DroidDetector == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor detector not found"));
	}
	else
	{
		TArray<UActorComponent*> Components = GetComponents();
		bool FoundSphereDetector = false;
		for (size_t i = 0; i < Components.Num() && !FoundSphereDetector; i++)
		{
			if (Components[i]->GetName().Equals("SphereDetector"))
			{
				FoundSphereDetector = true;
				DroidDetector->SetSphereComponent(Cast<USphereComponent>(Components[i]));
			}
		}
	}
}

void ADroid::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (MothershipActor != nullptr)
	{
		//Rotation
		RunningTime += DeltaSeconds;

		FRotator OffsetRotator = FRotator::ZeroRotator;
		OffsetRotator.Pitch = FMath::Sin(RunningTime) * OffsetAngleRotation;
		OffsetRotator.Yaw = FMath::Sin(RunningTime) * OffsetAngleRotation;

		FRotator ActorRotator = GetActorRotation();
		ActorRotator = FMath::RInterpTo(ActorRotator, (MothershipActor->GetActorRotation() + OffsetRotator), DeltaSeconds, RotationSpeed*DeltaSeconds);
		SetActorRotation(ActorRotator);

		// Movement
		FVector ActorForward = GetActorForwardVector();
		SetActorLocation(GetActorLocation() + (ActorForward * ForwardSpeed * DeltaSeconds));
		DrawDebugLine(
			GetWorld(),
			GetActorLocation(),
			GetActorLocation() + (ActorForward * ForwardSpeed),
			FColor(0, 0, 255),
			false, 10, 0,
			12.333
			);
	}
}
#pragma endregion

#pragma region DROID
void ADroid::SetMothershipActor(AActor* Mothership)
{
	MothershipActor = Mothership;
}

void ADroid::OnSeePawn(APawn* OtherPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("See %s"), *(OtherPawn->GetName()));
}
#pragma endregion

