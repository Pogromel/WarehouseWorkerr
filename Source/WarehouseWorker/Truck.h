// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Truck.generated.h"

UCLASS()
class WAREHOUSEWORKER_API ATruck : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATruck();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY()
	UStaticMeshComponent* BaseMesh;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
