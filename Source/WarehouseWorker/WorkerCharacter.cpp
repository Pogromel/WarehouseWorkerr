// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkerCharacter.h"
#include "DrawDebugHelpers.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AWorkerCharacter::AWorkerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Initialize CameraComponent
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    if (CameraComponent)
    {
        CameraComponent->SetupAttachment(RootComponent); // Assuming RootComponent exists
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to initialize CameraComponent in AWorkerCharacter"));
    }
}

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

void AWorkerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

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

    
    FVector Start = CameraComponent->GetComponentLocation();
    FVector End = Start + CameraComponent->GetComponentRotation().Vector() * 5000.0f;
  
    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
     
   if  (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, Params))
   {
       UE_LOG(LogTemp, Warning, TEXT("HitSomething"));
       if (HitResult.GetActor())
       {
           UE_LOG(LogTemp, Warning, TEXT("HitSomething: &S"), *HitResult.GetActor()->GetName());
       }
   }
}

void AWorkerCharacter::Drop(const FInputActionValue& Value)
{
   // UE_LOG(LogTemp, Warning, TEXT("Droping"));
}




