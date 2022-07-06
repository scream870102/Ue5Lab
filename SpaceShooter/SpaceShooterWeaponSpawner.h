// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceShooterObstacleManager.h"
#include "GameFramework/Actor.h"
#include "SpaceShooterWeaponSpawner.generated.h"

class ASpaceShooterWeaponContainer;
UCLASS()
class UE5LAB_API ASpaceShooterWeaponSpawner : public AActor
{
	GENERATED_BODY()

public:
	ASpaceShooterWeaponSpawner();
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

protected:
	void OnLevelStart();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual  void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


protected:
	UPROPERTY(EditAnywhere, Category = "Setting")
		TArray<TSubclassOf<ASpaceShooterWeaponContainer>>	 WeaponContainerTemplates;
	UPROPERTY(VisibleAnywhere, Category = "Setting")
		TSubclassOf<ASpaceShooterWeaponContainer> LastSpawn;
	UPROPERTY(EditAnywhere, Category = "Setting")
		TArray<AActor*> SpawnAnchor;
	UPROPERTY(VisibleAnywhere, Category = "Debug")
		ASpaceShooterWeaponContainer* CurrentContainer;
	FDelegateHandle OnLevelStartDelegateHandle;
};
