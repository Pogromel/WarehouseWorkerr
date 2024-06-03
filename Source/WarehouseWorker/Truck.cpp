


#include "Truck.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "Materials/MaterialInstanceDynamic.h" 
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"


// Sets default values
ATruck::ATruck()
{
    PrimaryActorTick.bCanEverTick = true;

    

    

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

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

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(BaseMesh);
	SpringArm->TargetArmLength = 500.0f; 
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	BoxTrigger-> CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	BoxTrigger-> SetupAttachment(BaseMesh);
	BoxTrigger->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	BoxTrigger->SetCollisionProfileName(TEXT("Trigger"));
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATruck::OnOverlapBegin); 
}

// Called when the game starts or when spawned
void ATruck::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(TruckMappingContext, 0);
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
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ATruck::MoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ATruck::MoveRight);
		
	}

}

void ATruck::MoveForward(const FInputActionValue& Value)
{
	const float AxisValue = Value.Get<float>();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("MoveForward AxisValue: %f"), AxisValue));
	if (AxisValue != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), AxisValue * MovementSpeed);
	}
}

void ATruck::MoveRight(const FInputActionValue& Value)
{
	const float AxisValue = Value.Get<float>();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("MoveRight AxisValue: %f"), AxisValue));
	if (AxisValue != 0.0f)
	{
		AddActorLocalRotation(FRotator(0.f, AxisValue * TurnSpeed * GetWorld()->GetDeltaSeconds(), 0.f));
	}
}


void ATruck::OnOverlapBegin(class  UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Overlapping Actor: %s"), *OtherActor->GetName()));
		OtherActor->Destroy();
	}
}

