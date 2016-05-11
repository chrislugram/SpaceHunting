// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Utils/LifeComponent.h"
#include "Enemy.generated.h"

UCLASS()
class SPACEHUNTING_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	ULifeComponent* LifeComponent;
	
	UFUNCTION(BlueprintCallable, Category = "Life")
	void Died();
};