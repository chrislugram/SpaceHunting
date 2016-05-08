// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpawnElement.h"
#include "ProjectileSpawn.generated.h"

/**
 * 
 */
UCLASS()
class SPACEHUNTING_API UProjectileSpawn : public USpawnElement
{
	GENERATED_BODY()
	
public:
	/** Initialize the spawn element */
	UFUNCTION(BlueprintCallable, Category = "SpawnComponent")
	virtual void InitElement(class USpawnComponent* Spawner) override;
};
