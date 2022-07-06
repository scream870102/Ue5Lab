// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SceneComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"

#include "SpaceShooterShootComponent.h"
#include "SpaceShooterHealthComponent.h"
#include "SpaceShooterHitAble.h"

#include "SpaceShooterPlayer.generated.h"

UCLASS()
class UE5LAB_API ASpaceShooterPlayer : public APawn, public ISpaceShooterHitAble
{
	GENERATED_BODY()

public:

	// Sets default values for this pawn's properties
	ASpaceShooterPlayer();

	UFUNCTION()
		void OnBeginOverlap(AActor* PlayerActor, AActor* OtherActor);


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveRight(float Axis);
	void MoveForward(float Axis);
	void StartFiring() const;
	void StopFiring() const;

	virtual void Hit(const float Damage, AActor* From) override;

	void GetWeapon(TSubclassOf<ASpaceShooterWeapon> NewWeaponBP) const;
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void UpdateRotation();
	void FixLocationIfNeeded();
	void UpdateLocation(float DeltaTime);


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:

	//TODO: Handle Pick up item
	void CollectablePickup();



public:

	TWeakObjectPtr<USceneComponent>	DefaultSceneRoot;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* ParticleSystems;
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* ExplosionFx;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ShipMesh;
	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CollisionComponent;
	UPROPERTY(EditAnywhere)
		UAudioComponent* DeathExplosionSound;

	UPROPERTY(EditAnywhere)
		float FieldWidth;
	UPROPERTY(EditAnywhere)
		float FieldHeight;

	UPROPERTY(EditAnywhere)
		float MaxVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USpaceShooterHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere)
		USpaceShooterShootComponent* ShootComponent;
protected:
	bool bHit;
	bool bDead;

private:
	float CurrentXVelocity;
	float CurrentYVelocity;

	FVector CurrentLocation;
	FRotator CurrentRotation;
	FVector NewLocation;

	UPROPERTY(EditAnywhere)
		FVector InitScale;

};

class FSpaceShooterPlayerEvents
{
public:
	DECLARE_EVENT(ASpaceShooterPlayer, FOnPlayerDead)

	static FOnPlayerDead OnPlayerDead;
};
