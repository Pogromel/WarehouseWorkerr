// Fill out your copyright notice in the Description page of Project Settings.


#include "Truck.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

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
	
	Pallete = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pallete Mesh"));
	Pallete->SetupAttachment(BaseMesh);
	
	Pallete2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pallete2 Mesh"));
	Pallete2->SetupAttachment(BaseMesh);


	
}

// Called when the game starts or when spawned
void ATruck::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(WorkerCharacterContext, 0);
		}
	}
	
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

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementTruck, ETriggerEvent::Triggered, this, &ATruck::Move);
		EnhancedInputComponent->BindAction(TurnTrack, ETriggerEvent::Triggered, this, &ATruck::Turn);
		
	}

}

void ATruck::Move(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();
	FVector ForwardVector = GetActorForwardVector();
	AddMovementInput(ForwardVector, AxisValue);
}

void ATruck::Turn(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();
	AddControllerYawInput(AxisValue);
}

