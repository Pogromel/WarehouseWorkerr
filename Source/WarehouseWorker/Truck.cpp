// Fill out your copyright notice in the Description page of Project Settings.


#include "Truck.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ATruck::ATruck()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);
}

// Called when the game starts or when spawned
void ATruck::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATruck::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATruck::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

