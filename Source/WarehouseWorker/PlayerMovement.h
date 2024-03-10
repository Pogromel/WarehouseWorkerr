// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerMovement.generated.h"

UCLASS()
class WAREHOUSEWORKER_API APlayerMovement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerMovement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; // similar to start class in unity 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override; // Similar to Update class in unity. 

	UPROPERTY(EditAnywhere, Category="Moving Platform")
	FVector PlatformVelocity = FVector(100, 0, 0);
	
	UPROPERTY(EditAnywhere, Category="Moving Platform")
	float MoveDistance = 500; // property of type float. 

	UPROPERTY(EditAnywhere, Category="Rotation Player")
	FRotator RotationVelocity;




	
	

	
	FVector StartLocation; // FVector is three dimensional vector in space 

	void PlayerMovement(float DeltaTime);

	void PlayerRotate(float DeltaTime);
	
};
