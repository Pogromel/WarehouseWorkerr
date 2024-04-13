

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "WorkerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USkeletalMeshComponent;

UCLASS()
class WAREHOUSEWORKER_API AWorkerCharacter : public ACharacter
{
	GENERATED_BODY()

	

public:
	AWorkerCharacter();




protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class USceneComponent* HoldingComponent;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	USceneComponent* HoldingSpot;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	FName HoldingSocketName;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	float HoldingOffsetX;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	float HoldingOffsetY;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	float HoldingOffsetZ;

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

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void PickUp(const FInputActionValue& Value);
	void Drop(const FInputActionValue& Value);

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
};