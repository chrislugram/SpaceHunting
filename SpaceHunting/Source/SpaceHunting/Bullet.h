// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProjectileSpawn.h"
#include "Bullet.generated.h"

UCLASS()
class SPACEHUNTING_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	class UProjectileSpawn* ProjectileSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;


	// Sets default values for this actor's properties
	ABullet();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to shoot this bullet
	UFUNCTION(BlueprintCallable, Category = "Bullet")
	void Shoot(FVector Direction);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float InitVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float Damage;

	// Is true when bullet is in movement
	bool InMovement;

	// Current direction in movement of this bullet
	FVector CurrentDirection;

	UFUNCTION(BlueprintCallable, Category = "Bullet")
	void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
