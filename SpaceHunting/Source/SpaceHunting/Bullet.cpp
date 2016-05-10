// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceHunting.h"
#include "Constant/Constants.h"
#include "Utils/LifeComponent.h"
#include "Bullet.h"

#pragma region CONSTRUCTORS
// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BulletSphereComponent"));
	if (SphereComponent != nullptr)
	{
		RootComponent = SphereComponent;
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);
	}
	
	ProjectileSpawn = CreateDefaultSubobject<UProjectileSpawn>(TEXT("ProjectileSpawn"));
}
#pragma endregion

#pragma region ENGINE
// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	InMovement = false;
	CurrentDirection = FVector::ZeroVector;
}

// Called every frame
void ABullet::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (InMovement)
	{
		AActor * BulletActor = GetRootComponent()->GetAttachmentRootActor();
		BulletActor->SetActorLocation(BulletActor->GetActorLocation() + (CurrentDirection * InitVelocity * DeltaTime));
	}
}
#pragma endregion

#pragma region BULLET
// Called to shoot this bullet
void ABullet::Shoot(FVector Direction)
{
	CurrentDirection = Direction;
	InMovement = true;
}
#pragma endregion

#pragma region EVENTS
void ABullet::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Error, TEXT("golpeo a %s"), *(OtherComp->GetName()));
	InMovement = false;
	if (OtherComp->ComponentHasTag(Constants::TAG_ENEMY))
	{
		UE_LOG(LogTemp, Error, TEXT("golpeo a ENEMY"));
		OtherActor->FindComponentByClass<ULifeComponent>()->ApplyDamage(-Damage);
	}
	else if (OtherComp->ComponentHasTag(Constants::TAG_MOTHERSHIP_ENEMY))
	{
		UE_LOG(LogTemp, Error, TEXT("golpeo a MOTHERSHIP"));
	}
	ProjectileSpawn->DisableElement();
}
#pragma endregion


