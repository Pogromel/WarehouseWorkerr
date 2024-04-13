// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkerCharacter.h"
#include "DrawDebugHelpers.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AWorkerCharacter::AWorkerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    HoldingSpot = CreateDefaultSubobject<USceneComponent>(TEXT("HoldingSpot"));
    if (HoldingSpot)
    {
        HoldingSpot->SetupAttachment(RootComponent);
    }
   
    
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    if (CameraComponent)
    {
        CameraComponent->SetupAttachment(RootComponent); // Assuming RootComponent exists
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
    FVector End = Start + CameraComponent->GetComponentRotation().Vector() * 500.0f;

    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
     
    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_WorldStatic, Params))
    {
        AActor* HitActor =  HitResult.GetActor();
        if (HitActor)
        {
            // Detach the actor first if it's already attached to something
            HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
            
            // Disable physics simulation
            UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(HitActor->GetRootComponent());
            if (PrimitiveComponent)
            {
                PrimitiveComponent->SetSimulatePhysics(false);
            }
            
            // Attach the actor to the HoldingSpot's root component
            HitActor->AttachToComponent(HoldingSpot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
        }
    }
}

void AWorkerCharacter::Drop(const FInputActionValue& Value)
{
    // Check if there's an item held on the HoldingSpot
    if (HoldingSpot->GetNumChildrenComponents() > 0)
    {
        // Get the first child component, assuming it's the held item
        USceneComponent* HeldItem = HoldingSpot->GetChildComponent(0);
        if (HeldItem)
        {
            // Enable physics simulation
            UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(HeldItem);
            if (PrimitiveComponent)
            {
                PrimitiveComponent->SetSimulatePhysics(true);
            }
            
            // Detach the held item from the HoldingSpot
            HeldItem->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
            
            // Optionally, you can add more logic here such as applying force to the dropped item
            
            // After dropping, you might want to nullify any reference to the held item
            
            // You can also add logging or other feedback to indicate that the item has been dropped
            UE_LOG(LogTemp, Warning, TEXT("Item dropped"));
        }
    }
}




