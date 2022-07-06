// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterOrbitRotateComponent.h"

#include "Ue5Lab/Utilities/Logger.h"

// Sets default values for this component's properties
USpaceShooterOrbitRotateComponent::USpaceShooterOrbitRotateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpaceShooterOrbitRotateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void USpaceShooterOrbitRotateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
	const FRotator PreviousRot = GetOwner()->GetActorRotation();
	FRotator NewRot = FRotator(PreviousRot.Pitch + RotationValue.Pitch * DeltaTime, PreviousRot.Yaw + RotationValue.Yaw * DeltaTime, PreviousRot.Roll + RotationValue.Roll * DeltaTime);
	GetOwner()->SetActorRotation(NewRot);
}

