#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "InputActionValue.h"
#include "WorkerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USkeletalMeshComponent;
class UTextBlock;
class ATruck;

UCLASS()
class WAREHOUSEWORKER_API AWorkerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AWorkerCharacter();

    // Add the SpawnBoxInHands method to the public section
    void SpawnBoxInHands();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "Pickup")
    USceneComponent* HoldingSpot;

    UPROPERTY(EditAnywhere, Category = "Pickup")
    USceneComponent* PickupLine;

    UPROPERTY(EditAnywhere, Category = "Pickup")
    FName HoldingSocketName;

    UPROPERTY(EditAnywhere)
    UCameraComponent* CameraComponent;

    UPROPERTY(EditAnywhere, Category = Input)
    UInputMappingContext* WorkerCharacterContext;

    UPROPERTY(EditAnywhere, Category = Input)
    UInputAction* MovementAction;

    UPROPERTY(EditAnywhere, Category = Input)
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, Category = Input)
    UInputAction* PickUpAction;

    UPROPERTY(EditAnywhere, Category = Input)
    UInputAction* DropAction;

    UPROPERTY(EditAnywhere, Category = Input)
    UInputAction* InteractAction;

    UPROPERTY(EditAnywhere)
    UPrimitiveComponent* FloorSplashPlane;

    UPROPERTY(EditAnywhere)
    UMaterialInterface* ScreenWaterSplashMaterial;

    UPROPERTY()
    UMaterialInstanceDynamic* PostProcessMaterialInstance;

    UPROPERTY(EditAnywhere, Category = "Interaction")
    float InteractionRange;

    UPROPERTY()
    bool bIsControllingTruck;

    UPROPERTY()
    ATruck* ControlledTruck;

    UPROPERTY(EditAnywhere, Category = "FallingLimit")
    float FallLimit = -170.0f;

    UPROPERTY(EditAnywhere, Category = "FallingLimit")
    FVector SafePosition = FVector(-644.0f, 7146.0f, 124);

    // Functions
    void SetPostProcessDynamicMaterialInstance();
    void ActivatePostProcessEffect();
    void OnFloorSplashPlaneCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void PickUp(const FInputActionValue& Value);
    void Drop(const FInputActionValue& Value);
    void Interact(const FInputActionValue& Value);
    void EnterTruck(ATruck* Truck);
    void ExitTruck();

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }

private:
    void CheckIfFalling();
};
