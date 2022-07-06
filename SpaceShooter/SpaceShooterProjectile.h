// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceShooterProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
UCLASS()
class UE5LAB_API ASpaceShooterProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpaceShooterProjectile();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Fire(const FVector& FireDir);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	UPROPERTY(EditAnywhere, Category = Projectile)
		USphereComponent* CollisionComponent;
	UPROPERTY(EditAnywhere, Category = Projectile)
		UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(EditAnywhere, Category = Projectile)
		UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditAnywhere)
		float LifeSpan = 3.0f;
	UPROPERTY(EditAnywhere)
		float Damage = 5.0f;


};
