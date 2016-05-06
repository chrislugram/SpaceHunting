// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SpawnElement.h"
#include "SpawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEHUNTING_API USpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	/** Called to spawn object in world */
	UFUNCTION(BlueprintCallable, Category = "SpawnComponent")
	void SpawnActor();

	/** Return the point where spawn a object*/
	UFUNCTION(BlueprintCallable, Category = "SpawnComponent")
	FVector GetSpawnPoint();

	/** Activate the spawn*/
	void FinishReloadTime();

	/** Stored the spawn elements disabled */
	void AddDisabledSpawnElement(class USpawnElement* SpawnElement);

protected:
	/** SpringArm used for the CameraComponent */
	UPROPERTY(EditAnywhere, Category = "SpawnComponent", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SpawnPoint;

	/** The object to spawn */
	UPROPERTY(EditAnywhere, Category = "SpawnComponent")
	TSubclassOf<class AActor> SpawnBP;

	/** Time waiting to reload the spawn component*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnComponent")
	float ReloadTime;

	/** Flag to wait to next spawn*/
	bool ReloadSpawn;

	/** Timer to control the reload time*/
	FTimerHandle SpawnTimer;

	/** Array with spawnElements disabled */
	TArray<class USpawnElement*> DisabledSpawnElements;
};
