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
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	/** Damage to player when have a collision */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Droid")
	float Damage;

	/** Speed of rotation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Droid")
	float RotationSpeed;

	/** Speed of forward movement */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Droid")
	float ForwardSpeed;

	/** Current rotation of the droid */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Droid")
	FRotator CurrentRotation;
};
