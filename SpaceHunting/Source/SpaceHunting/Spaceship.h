// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Constant/Constants.h"
#include "Spaceship.generated.h"

class ULifeComponent;
class USpawnComponent;

UCLASS()
class SPACEHUNTING_API ASpaceship : public APawn
{
	GENERATED_BODY()

public:
	/** SpringArm used for the CameraComponent */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraSpringArm;

	/** Follow camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	/** Spaceship movement */
	class UFloatingPawnMovement* FloatingMovement;

	// Sets default values for this pawn's properties
	ASpaceship();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Called when the life of player change
	UFUNCTION(BlueprintCallable, Category = "Life")
	void SpaceshipLifeChange(float Life);

	// Called when player die
	UFUNCTION(BlueprintCallable, Category = "Life")
	void SpaceshipDestroyed();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship", meta = (AllowPrivateAccess = "true"))
	float SpeedRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship", meta = (AllowPrivateAccess = "true"))
	float MaxSpeedForward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship", meta = (AllowPrivateAccess = "true"))
	float AccelerationForward;

	/** SpawnComponent */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship")
	class USpawnComponent* SpawnComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship")
	class ULifeComponent* LifeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	float CurrentSpeedForward;

	UFUNCTION(BlueprintCallable, Category = "Spaceship")
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

///	INPUT_METHODS
	/** Called for rotation in X axis */
	void RotateXAxis(float RotationValue);

	/** Called for rotation in Y axis */
	void RotateYAxis(float RotationValue);

	/** Called for acceleration change*/
	void AccelerationAxis(float AccelerationValue);

	/** Called for shoot Axis*/
	void Shoot(float ShootAxis);
};
