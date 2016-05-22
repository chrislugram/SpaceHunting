// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "LifeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLifeChangeDelegate, float, Life);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLifeEndDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEHUNTING_API ULifeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULifeComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	/** Apply damage to life, can be positive or negative */
	UFUNCTION(BlueprintCallable, Category = "Life")
	void ApplyDamage(float Damage);

	/** Reset life */
	UFUNCTION(BlueprintCallable, Category = "Life")
	void ResetLife();

	/** Delegate, executed when CurrentLife changes*/
	UPROPERTY(BlueprintAssignable)
	FLifeChangeDelegate LifeChangeDelegate;

	/** Delegate, executed when CurrentLife < 0*/
	UPROPERTY(BlueprintAssignable)
	FLifeEndDelegate DiedDelegate;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Life")
	float InitLife;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Life")
	float CurrentLife;
};
