// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkerCharacter.h"

// Sets default values
AWorkerCharacter::AWorkerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorkerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorkerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWorkerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MovingForward"), this, &AWorkerCharacter::MovingForward);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);

}

void AWorkerCharacter::MovingForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

// void AWorkerCharacter::LookUp(float AxisValue)
// {
// 	AddControllerPitchInput(AxisValue);
// }


