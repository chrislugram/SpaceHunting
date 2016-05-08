// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Spaceship.generated.h"

UCLASS()
class SPACEHUNTING_API ASpaceship : public APawn
{
	GENERATED_BODY()

public:
#pragma region FIELDS
	/** SpringArm used for the CameraComponent */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraSpringArm;

	/** Follow camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	/** Spaceship movement */
	class UFloatingPawnMovement* FloatingMovement;
#pragma endregion

#pragma region CONSTRUCTORS
	// Sets default values for this pawn's properties
	ASpaceship();
#pragma endregion

#pragma region METHODS
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
#pragma endregion
protected:
#pragma region FIELDS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship", meta = (AllowPrivateAccess = "true"))
	float SpeedRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship", meta = (AllowPrivateAccess = "true"))
	float MaxSpeedForward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship", meta = (AllowPrivateAccess = "true"))
	float AccelerationForward;

	/** SpawnComponent */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship", meta = (AllowPrivateAccess = "true"))
	class USpawnComponent* SpawnComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	float CurrentSpeedForward;
#pragma endregion

#pragma region INPUT_METHODS
	/** Called for rotation in X axis */
	void RotateXAxis(float RotationValue);

	/** Called for rotation in Y axis */
	void RotateYAxis(float RotationValue);

	/** Called for acceleration change*/
	void AccelerationAxis(float AccelerationValue);

	/** Called for shoot Axis*/
	void Shoot(float ShootAxis);
#pragma endregion
};
