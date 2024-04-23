
#include "WorkerCharacter.h" 
#include "Components/InputComponent.h" 
#include "DrawDebugHelpers.h" 
#include "EnhancedInputComponent.h" 
#include "EnhancedInputSubsystems.h" 
#include "Materials/MaterialInstanceDynamic.h" 
#include "Components/PrimitiveComponent.h" 

AWorkerCharacter::AWorkerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    //Holding Position
    HoldingSpot = CreateDefaultSubobject<USceneComponent>(TEXT("HoldingSpot"));
    if (HoldingSpot)
    {
        HoldingSpot->SetupAttachment(RootComponent);
    }
   
    //CameraPosition
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    if (CameraComponent)
    {
        CameraComponent->SetupAttachment(RootComponent); 
    }
    
    
    
   
    
}

void AWorkerCharacter::BeginPlay()
{
    Super::BeginPlay();
    //Character Movement
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(WorkerCharacterContext, 0);
        }
    }
    
    //PostProcessEffect
    if (FloorSplashPlane)
    {
        FloorSplashPlane->OnComponentBeginOverlap.AddDynamic(this, &AWorkerCharacter::OnFloorSplashPlaneCollision);
    }

    // Set up post-process material instance
    SetPostProcessDynamicMaterialInstance();
    
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
            
            HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
            
            
            UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(HitActor->GetRootComponent());
            if (PrimitiveComponent)
            {
                PrimitiveComponent->SetSimulatePhysics(false);
            }
            
            
            HitActor->AttachToComponent(HoldingSpot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
        }
    }
}

void AWorkerCharacter::Drop(const FInputActionValue& Value)
{
    
    if (HoldingSpot->GetNumChildrenComponents() > 0)
    {
        
        USceneComponent* HeldItem = HoldingSpot->GetChildComponent(0);
        if (HeldItem)
        {
           
            UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(HeldItem);
            if (PrimitiveComponent)
            {
                PrimitiveComponent->SetSimulatePhysics(true);
            }
            
         
            HeldItem->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
            
            UE_LOG(LogTemp, Warning, TEXT("Item dropped"));
        }
    }
}

void AWorkerCharacter::SetPostProcessDynamicMaterialInstance()
{
    if (ScreenWaterSplashMaterial)
    {
        // Create dynamic material instance
        PostProcessMaterialInstance = UMaterialInstanceDynamic::Create(ScreenWaterSplashMaterial, this);

        if (PostProcessMaterialInstance)
        {
            // Additional setup for the dynamic material instance if needed
        }
    }
}

void AWorkerCharacter::ActivatePostProcessEffect()
{
   
    if (PostProcessMaterialInstance)
    {
        // Set scalar parameter to activate the effect
        PostProcessMaterialInstance->SetScalarParameterValue(TEXT("ActivateEffect"), 1.0f);
    }
}

void AWorkerCharacter::OnFloorSplashPlaneCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    
    if (OverlappedComponent == FloorSplashPlane)
    {
        // Activate the post-process effect
        ActivatePostProcessEffect();
    }
}








