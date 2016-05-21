// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ActorDetectorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActorDetectorDelegate, AActor*, ActorDetected);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEHUNTING_API UActorDetectorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorDetectorComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Called to setup the sphere component
	UFUNCTION(BlueprintCallable, Category = "ActorDetector")
	void SetSphereComponent(USphereComponent* SphereComponent);

	// Called each detection
	UFUNCTION(BlueprintCallable, Category = "ActorDetector")
	void RunDetection();

	// Delegate launched when an actor was detected
	UPROPERTY(BlueprintAssignable)
	FActorDetectorDelegate ActorDetected;

protected:
	/** Max angle of detection*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorDetector")
	float MaxAngleDetection;
	
	/** Max distance of detection*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorDetector")
	float MaxDistanceDetection;

	/** Time that pass between two detections*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorDetector")
	float TimeBetweenDetections;

	/** Tag to detect in overlapping actors*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorDetector")
	FName TagToDetect;

	/** Timer to control detections*/
	FTimerHandle DetectorTimer;

	/** Sphere detect overlaping actors*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorDetector")
	class USphereComponent* SphereDetector;
};
