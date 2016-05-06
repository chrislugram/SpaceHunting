// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SpawnComponent.h"
#include "SpawnElement.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEHUNTING_API USpawnElement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnElement();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	/** Initialize the spawn element */
	void InitElement(class USpawnComponent* Spawner);

	/** Disable actor*/
	void DisableElement();

	/** Enable actor */
	void EnableElement();

protected:
	/** Time to disable the spawn element */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnElement", meta = (AllowPrivateAccess = "true"))
	float DisableTime;

	/** SpawnComponent who initialize the spawn element */
	class USpawnComponent* SpawnerOwner;

	/** Timer to control the reload time*/
	FTimerHandle EnableTimer;
};
