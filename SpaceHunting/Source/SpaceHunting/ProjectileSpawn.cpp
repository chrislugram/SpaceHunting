// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceHunting.h"
#include "Bullet.h"
#include "ProjectileSpawn.h"

#pragma region SPAWN_ELEMENT
void UProjectileSpawn::InitElement(USpawnComponent* Spawner)
{
	Super::InitElement(Spawner);

	ABullet* Bullet = Cast<ABullet>(GetOwner());
	if (Bullet != nullptr)
	{
		Bullet->Shoot(GetOwner()->GetActorForwardVector());
	}
}
#pragma endregion
