// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterShotgun.h"

#include "SpaceShooterShootComponent.h"
#include "Ue5Lab/Utilities/Logger.h"

void ASpaceShooterShotgun::Firing()
{
	const FVector Forward = ShootComponent->GetForwardVector();
	for (int i = 0; i < BulletsPerShoot; i++)
	{
		const FVector PosDir = Forward.RotateAngleAxis(ShootRangeRadiusInDegree * i, FVector::ZAxisVector);
		const FVector NegDir = Forward.RotateAngleAxis(-ShootRangeRadiusInDegree * i, FVector::ZAxisVector);




		SpawnProjectile(PosDir);
		SpawnProjectile(NegDir);

	}
}
