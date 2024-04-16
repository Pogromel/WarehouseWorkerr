// Fill out your copyright notice in the Description page of Project Settings.


#include "Truck.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ATruck::ATruck()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	SpringArm  = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	Wheels = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheels Mesh"));
	Wheels->SetupAttachment(BaseMesh);

	Buttons = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Buttons Mesh"));
	Buttons->SetupAttachment(BaseMesh);

	Wheel_Rolls = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel_Rolls Mesh"));
	Wheel_Rolls->SetupAttachment(BaseMesh);

	
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

