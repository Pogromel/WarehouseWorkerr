// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMovement.h"

// Sets default values
APlayerMovement::APlayerMovement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerMovement::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	
}

// Called every frame
void APlayerMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayerMovement(DeltaTime);
	PlayerRotate(DeltaTime);
}

void APlayerMovement::PlayerMovement(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation(); // current location of the cube. that is attached to script
	CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime); //its updating the location of the "Actor (Cube)" based on platformvelocity (x = 100, y = 0, z = 0. * deltatime to keep it the same on any pc slower or faster)
	SetActorLocation(CurrentLocation);

	//FVector::Dist calculates the eucildean distance between to vectors, start and current
	float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);

	// simple if statement that checks if the cube moved less thant distancemoved which is assigned to 500. if yes then reverse direction
	if (DistanceMoved > MoveDistance) 
	{
		
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
}

void APlayerMovement::PlayerRotate(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);

	

}



