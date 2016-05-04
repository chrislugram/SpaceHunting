// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceHunting.h"
#include "Spaceship.h"

#define OUT

#pragma region CONSTRUCTORS
ASpaceship::ASpaceship()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create empty root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SpaceshipRoot"));

	// Create spring arm
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->AttachTo(RootComponent);
	CameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 30.0f), FRotator(-40.0f, 0.0f, 0.0f));
	CameraSpringArm->TargetArmLength = 250.f;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->CameraLagSpeed = 20.00f;
	
	// Create a camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachTo(CameraSpringArm, USpringArmComponent::SocketName);

	// Create spaceship movement
	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
	FloatingMovement->UpdatedComponent = RootComponent;

	// Posses default Player 0
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}
#pragma endregion

#pragma region ENGINE
// Called when the game starts or when spawned
void ASpaceship::BeginPlay()
{
	Super::BeginPlay();	

	// Setup movement
	ForwardAxis = 0;
	CurrentSpeedForward = 0;
}

// Called every frame
void ASpaceship::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	// Update speed
	CurrentSpeedForward += ForwardAxis * DeltaTime * AccelerationForward;

	// Clamp speed
	if ((CurrentSpeedForward > 0) && (CurrentSpeedForward > MaxSpeedForward))
		CurrentSpeedForward = MaxSpeedForward;
	else if ((CurrentSpeedForward < 0) && (CurrentSpeedForward < -MaxSpeedForward))
		CurrentSpeedForward = -MaxSpeedForward;
	else if (CurrentSpeedForward == 0)
		CurrentSpeedForward = 0;

	UE_LOG(LogTemp, Warning, TEXT("SPEED: %f"), CurrentSpeedForward);

	// ApplySpeed
	FloatingMovement->AddInputVector(GetActorForwardVector() * CurrentSpeedForward);
}
#pragma endregion

#pragma region INPUT
// Called to bind functionality to input
void ASpaceship::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("XAxis", this, &ASpaceship::RotateXAxis);
	InputComponent->BindAxis("YAxis", this, &ASpaceship::RotateYAxis);
	
	InputComponent->BindAction("ForwardEvent", EInputEvent::IE_Pressed, this, &ASpaceship::MoveForward);
	InputComponent->BindAction("BackwardEvent", EInputEvent::IE_Pressed, this, &ASpaceship::MoveBackward);
}

void ASpaceship::RotateXAxis(float RotationValue)
{
	FRotator ActorRotation = GetActorRotation();
	FQuat QuatRotation = ActorRotation.Quaternion();
	FQuat AddingQuatRotation = FRotator(RotationValue * SpeedRotation, 0, 0).Quaternion();
	FQuat NewQuatRotation = QuatRotation * AddingQuatRotation;
	SetActorRotation(NewQuatRotation.Rotator());
}

void ASpaceship::RotateYAxis(float RotationValue)
{
	FRotator ActorRotation = GetActorRotation();
	FQuat QuatRotation = ActorRotation.Quaternion();
	FQuat AddingQuatRotation = FRotator(0, RotationValue * SpeedRotation, 0).Quaternion();
	FQuat NewQuatRotation = QuatRotation * AddingQuatRotation;
	SetActorRotation(NewQuatRotation.Rotator());
}

void ASpaceship::MoveForward()
{
	if (ForwardAxis < 0)
		ForwardAxis = 0;
	else
		ForwardAxis = 1;
}

void ASpaceship::MoveBackward()
{
	if (ForwardAxis > 0)
		ForwardAxis = 0;
	else
		ForwardAxis = -1;
}
#pragma endregion

