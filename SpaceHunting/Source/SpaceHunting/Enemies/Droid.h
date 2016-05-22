// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemies/Enemy.h"
#include "Utils/ActorDetectorComponent.h"
#include "SpawnElement.h"
#include "Droid.generated.h"

UENUM(BlueprintType)
enum class EDroidState : uint8
{
	DS_NONE			UMETA(DisplayName = "None"),
	DS_GUARD		UMETA(DisplayName = "Guard"),
	DS_HUNTING		UMETA(DisplayName = "Hunting")
};

/**
 * 
 */
UCLASS()
class SPACEHUNTING_API ADroid : public AEnemy
{
	GENERATED_BODY()
	
public:
	ADroid();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/** Setting the actor of the mothership */
	void SetMothershipActor(AActor* Mothership);

	/** Action when droid detect other actor*/
	UFUNCTION(BlueprintCallable, Category = "Droid")
	void OnActorDetected(AActor* ActorDetected);

	/** Initialized the droid*/
	UFUNCTION(BlueprintCallable, Category = "Droid")
	void InitDroid();

	/** Damage to player when have a collision */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Droid")
	float Damage;

protected:
	/** State of droid*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Droid State")
	EDroidState DroidState;

	/** Speed of rotation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Droid")
	float RotationSpeed;

	/** Offset of rotation*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Droid")
	float OffsetAngleRotation;

	float RunningTime;

	/** Speed of forward movement */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Droid")
	float ForwardSpeed;

	/** Speed of forward movement */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Droid")
	float MultiplyHuntingSpeed;

	/** Current rotation of the droid */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Droid")
	FRotator CurrentRotation;

	/** Actor of the mothership */
	AActor* MothershipActor;

	/** Actor to hunting*/
	AActor* ActorToHunt;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DroidComponents")
	class UActorDetectorComponent* DroidDetector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DroidComponents")
	class USpawnElement* SpawnElement;

	/** The movement of the droid when it is in guard state*/
	void GuardMovement(float DeltaSeconds);

	/** The movement of the droid when it is in hunting state*/
	void HuntingMovement(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "Life")
	void Died() override;
};
