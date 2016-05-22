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

	// Setup state
	DroidState = EDroidState::DS_NONE;

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
		// Setup the sphere of detection
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

		// Adding binding actions
		UE_LOG(LogTemp, Error, TEXT("añado delegados"));
		DroidDetector->ActorDetected.AddDynamic(this, &ADroid::OnActorDetected);
	}

	// Setup spawn element
	SpawnElement = FindComponentByClass<USpawnElement>();
	if (SpawnElement == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnElement not found"));
	}
	else
	{
		SpawnElement->EnabledDelegate.AddDynamic(this, &ADroid::InitDroid);
	}
}

void ADroid::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Select the movement of droid
	if (DroidState == EDroidState::DS_GUARD)
	{
		GuardMovement(DeltaSeconds);
	}
	else if (DroidState == EDroidState::DS_HUNTING)
	{
		HuntingMovement(DeltaSeconds);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Error state in droid %s"), *(GetName()));
	}
}
#pragma endregion

#pragma region DROID
void ADroid::InitDroid()
{
	// Restore life
	LifeComponent->ResetLife();

	// Clean actor to hunt
	ActorToHunt = nullptr;

	// Setup the initial state
	DroidState = EDroidState::DS_GUARD;

	// Clean running time
	RunningTime = FMath::RandRange(0.0f, 360.00f);
	//UE_LOG(LogTemp, Warning, TEXT("Random for droid %s: %f"), *(GetName()), RunningTime);
}

void ADroid::GuardMovement(float DeltaSeconds)
{
	if (MothershipActor != nullptr)
	{
		// Adding offset rotation
		RunningTime += DeltaSeconds;

		FRotator OffsetRotator = FRotator::ZeroRotator;
		OffsetRotator.Pitch = FMath::Sin(RunningTime) * OffsetAngleRotation;
		OffsetRotator.Yaw = FMath::Cos(RunningTime) * OffsetAngleRotation;

		//Rotation
		FRotator ActorRotator = GetActorRotation();
		ActorRotator = FMath::RInterpTo(ActorRotator, (MothershipActor->GetActorRotation() + OffsetRotator), DeltaSeconds, RotationSpeed*DeltaSeconds);
		SetActorRotation(ActorRotator);

		// Movement
		FVector ActorForward = GetActorForwardVector();
		SetActorLocation(GetActorLocation() + (ActorForward * ForwardSpeed * DeltaSeconds));
		//DrawDebugLine( GetWorld(), GetActorLocation(), GetActorLocation() + (ActorForward * ForwardSpeed), FColor(0, 0, 255), false, 10, 0, 12.333);
	}
}

void ADroid::HuntingMovement(float DeltaSeconds)
{
	if (ActorToHunt != nullptr)
	{
		// Adding offset rotation
		RunningTime += (DeltaSeconds * MultiplyHuntingSpeed);

		FRotator OffsetRotator = FRotator::ZeroRotator;
		OffsetRotator.Pitch = FMath::Sin(RunningTime) * (OffsetAngleRotation * MultiplyHuntingSpeed);
		OffsetRotator.Yaw = FMath::Cos(RunningTime) * (OffsetAngleRotation * MultiplyHuntingSpeed);

		// Rotation
		FRotator ActorRotator = GetActorRotation();
		FRotator NewRotator = FRotationMatrix::MakeFromX(ActorToHunt->GetActorLocation() - GetActorLocation()).Rotator();
		ActorRotator = FMath::RInterpTo(ActorRotator, NewRotator + OffsetRotator, DeltaSeconds, RotationSpeed * DeltaSeconds * MultiplyHuntingSpeed);
		SetActorRotation(ActorRotator);

		// Movement
		FVector ActorForward = GetActorForwardVector();
		SetActorLocation(GetActorLocation() + (ActorForward * ForwardSpeed * DeltaSeconds * MultiplyHuntingSpeed));
	}
}

void ADroid::SetMothershipActor(AActor* Mothership)
{
	MothershipActor = Mothership;
}

void ADroid::OnActorDetected(AActor* ActorDetected)
{
	ActorToHunt = ActorDetected;
	DroidState = EDroidState::DS_HUNTING;
}

void ADroid::Died() 
{	
	SpawnElement->DisableElement();
}
#pragma endregion

