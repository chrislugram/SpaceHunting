// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemies/Enemy.h"
#include "SpawnComponent.h"
#include "MothershipEnemy.generated.h"

/**
 * 
 */
UCLASS()
class SPACEHUNTING_API AMothershipEnemy : public AEnemy
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor
	AMothershipEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "MothershipEnemy")
	void UpdateRotation();

	UFUNCTION(BlueprintCallable, Category = "MothershipEnemy Spawner")
	void CheckDroidGeneration();

	UFUNCTION(BlueprintCallable, Category = "MothershipEnemy Spawner")
	void DroidDestroyed();

protected:
	/** When the mothership have this energy, the game end */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MothershipEnemy")
	float EnergyToEnd;

	/** The speed of generation of energy*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MothershipEnemy")
	float EnergySpeedGeneration;

	/** Current energy accumulated */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MothershipEnemy")
	float CurrentEnergy;

	/** Time between each change of rotation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MothershipEnemy")
	float TimeToChangeRotation;

	/** Speed of rotation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MothershipEnemy")
	float RotationSpeed;

	/** Speed of forward movement */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MothershipEnemy")
	float ForwardSpeed;

	/** Timer to control the rotation time*/
	FTimerHandle RotationTimer;

	/** Current rotation of the mothership */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MothershipEnemy")
	FRotator CurrentRotation;

	/** Array of SpawnComponents */
	class USpawnComponent* SpawnComponent;

	/** Maximum droids generated by mothership*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MothershipEnemy Spawner")
	int MaxDroids;

	/** Current droids generated by mothership*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MothershipEnemy Spawner")
	int CurrentDroids;

	/** Time between droid generation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MothershipEnemy Spawner")
	float TimeToCreateDroid;

	/** Timer to control the droid generation time*/
	FTimerHandle DroidGenerationTimer;
};
