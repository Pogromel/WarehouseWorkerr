

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "InputActionValue.h"
#include "Truck.generated.h"


class UInputMappingContext;
class UInputAction;

UCLASS()
class WAREHOUSEWORKER_API ATruck : public APawn
{
	GENERATED_BODY()

public:
	ATruck();

	void Move(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* WorkerCharacterContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MovementTruck;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* TurnTrack;

	

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Wheels;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Buttons;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Wheel_Rolls;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Pallete;
    	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Pallete2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* PlayerPosition;


	

public:
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	USceneComponent* GetPlayerPositionComponent() const { return PlayerPosition; }

};
