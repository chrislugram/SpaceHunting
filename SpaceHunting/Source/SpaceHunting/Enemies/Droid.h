// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemies/Enemy.h"
#include "Droid.generated.h"

/**
 * 
 */
UCLASS()
class SPACEHUNTING_API ADroid : public AEnemy
{
	GENERATED_BODY()
	
public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
	/** Setting the actor of the mothership */
	void SetMothershipActor(AActor* Mothership);

protected:
	/** Damage to player when have a collision */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Droid")
	float Damage;

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

	/** Current rotation of the droid */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Droid")
	FRotator CurrentRotation;

	/** Actor of the mothership */
	AActor* MothershipActor;
};
