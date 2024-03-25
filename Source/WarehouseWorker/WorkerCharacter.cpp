// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkerCharacter.h"
#include "DrawDebugHelpers.h"


// Sets default values
AWorkerCharacter::AWorkerCharacter()
{
	// Set this character to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HoldingComponent = CreateDefaultSubobject<USceneComponent>(TEXT("HoldingComponent"));
	HoldingComponent->SetupAttachment(RootComponent); // Attach to the root component of the character

	// Set the relative location of the holding component (You may need to adjust this based on your character's skeletal mesh)
	HoldingComponent->SetRelativeLocation(FVector(50.0f, 0.0f, 0.0f));

	CurrentItem = nullptr;
	bCanMove = true;
	

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

	PlayerInputComponent->BindAxis(TEXT("MovingSideways"), this, &AWorkerCharacter::MovingSideways);

	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AWorkerCharacter::OnAction);

	PlayerInputComponent->BindAction("DeInteract", IE_Released, this, &AWorkerCharacter::OnActionReleased);
	

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookSideways"), this, &APawn::AddControllerYawInput);
}

void AWorkerCharacter::MovingForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}
void AWorkerCharacter::MovingSideways(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
	
}

void AWorkerCharacter::OnAction()
{
	// Check if there's a current item to pick up
	if (CurrentItem)
	{
		// Call the pickup function of the current item
		CurrentItem->Pickup();
	}
}

void AWorkerCharacter::OnActionReleased()
{
	// Release the item if it's currently being held
	if (CurrentItem && CurrentItem->bHolding)
	{
		// Call the pickup function of the current item again to release it
		CurrentItem->Pickup();
	}
}



