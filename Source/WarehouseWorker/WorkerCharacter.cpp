// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkerCharacter.h"
#include "DrawDebugHelpers.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AWorkerCharacter::AWorkerCharacter()
{
	// Set this character to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

}

// Called when the game starts or when spawned
void AWorkerCharacter::BeginPlay()
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
void AWorkerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWorkerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AWorkerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWorkerCharacter::Look);
		
		EnhancedInputComponent->BindAction(PickUpAction, ETriggerEvent::Started, this, &AWorkerCharacter::PickUp);
		EnhancedInputComponent->BindAction(DropAction, ETriggerEvent::Started, this, &AWorkerCharacter::Drop);
	}
	
}




void AWorkerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);

	
	
}

void AWorkerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void AWorkerCharacter::PickUp(const FInputActionValue& Value)
{
	UCameraComponent* Camera = (UCameraComponent*)(GetMesh()->GetChildComponent(0));
	FVector CameraWorldLocation = Camera->GetComponentLocation();
	FVector ForwardVector = Camera->GetForwardVector() * 300.0f;
	FVector InteractionVector = CameraWorldLocation + ForwardVector;
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;
	FHitResult RV_Hit(ForceInit);

	bool HitActor = GetWorld()->LineTraceSingleByChannel(
		RV_Hit,
		CameraWorldLocation,
		InteractionVector,
		ECC_Visibility,
		RV_TraceParams
		);

	if (HitActor)
	{
		if (RV_Hit.Actor->ActorHasTag(TEXT("Pickup")))
		{
			if (RV_Hit.Actor->ActorHasTag(TEXT("Box")))
			{
				UStaticMeshComponent* BoxMesh = (UStaticMeshComponent*)(GetMesh()->GetChildComponent(1));
				BoxMesh->SetVisibility(true, true);
			}
			RV_Hit.Actor->Destroy();
		}
	}
}

void AWorkerCharacter::Drop(const FInputActionValue& Value)
{
	
}








