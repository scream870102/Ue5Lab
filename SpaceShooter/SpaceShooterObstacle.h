// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceShooterHitAble.h"
#include "SpaceShooterObstacle.generated.h"

class UProjectileMovementComponent;
class UUserWidget;
class USpaceShooterHealthBarUserWidget;
UCLASS()
class UE5LAB_API ASpaceShooterObstacle : public AActor, public  ISpaceShooterHitAble
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ASpaceShooterObstacle();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Hit(const float Damage, AActor* Other) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void SetVelocity(FVector NewVel = FVector::ZeroVector) const;

	virtual void PendingDestroy();

	bool ShouldBeDestroy() const;

	UFUNCTION()
		virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
protected:
	UPROPERTY(EditAnywhere, Category = "Obstacle")
		UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(EditAnywhere, Category = "Obstacle")
		UPrimitiveComponent* Collision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
		UParticleSystemComponent* ExplosionFx;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
		UPrimitiveComponent* Renderer;
	UPROPERTY(EditAnywhere, Category = "Obstacle")
		float InitialHealth;
	UPROPERTY(EditAnywhere, Category = "Obstacle")
		float Damage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacle")
		float CurrentHealth;
	UPROPERTY(EditAnywhere, Category = "Obstacle")
		FVector InitialSpeedRangeMin;
	UPROPERTY(EditAnywhere, Category = "Obstacle")
		FVector InitialSpeedRangeMax;
	UPROPERTY(EditAnywhere)
		TSubclassOf<USpaceShooterHealthBarUserWidget> HPWidget;
	UPROPERTY(VisibleAnywhere, Category = "Debug")
		FVector VelocityCache;
	UPROPERTY(VisibleAnywhere, Category = "Debug")
		FVector LocationCache;
	UPROPERTY(EditAnywhere, Category = "Obstacle")
		float RotationVelocityMin;
	UPROPERTY(EditAnywhere, Category = "Obstacle")
		float RotationVelocityMax;
	UPROPERTY(EditAnywhere, Category = "Obstacle")
		float ExplosionFxElapsed;
	UPROPERTY(EditAnywhere, Category = "Obstacle")
		float LifeTime;
private:
	UPROPERTY()
		USpaceShooterHealthBarUserWidget* HealthUI;
	FRotator PerRotation;
};

class FSpaceShooterObstacleEvents
{
public:
	DECLARE_EVENT_OneParam(ASpaceShooterObstacle, FOnObstacleExplode, const ASpaceShooterObstacle* Obstacle)

	static FOnObstacleExplode OnObstacleExplode;

	DECLARE_EVENT_OneParam(ASpaceShooterObstacle, FOnObstacleDestroy, ASpaceShooterObstacle* Obstacle)

	static  FOnObstacleDestroy OnObstacleDestroy;
};
