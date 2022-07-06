// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SpaceShooterWeapon.generated.h"

class ASpaceShooterProjectile;
class USpaceShooterShootComponent;

UCLASS()
class UE5LAB_API ASpaceShooterWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpaceShooterWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual bool IsWeaponHasParent();
	virtual bool IsFiring();
	virtual void Init(USpaceShooterShootComponent* Parent);
	virtual void Disarm();
	virtual void StartFiring();
	virtual void StopFiring();
	virtual void Firing();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SpawnProjectile(const FVector ShootDir);



public:

protected:
	FTimerHandle  FireTimerHandler;
	bool HasParent;
	bool IsFire;
	UPROPERTY()
		USpaceShooterShootComponent* ShootComponent;
	UPROPERTY(EditAnywhere)
		float BasicDamage;
	UPROPERTY(EditAnywhere)
		float FireRate;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ASpaceShooterProjectile> WeaponProjectileBP;



};
