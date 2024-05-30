

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
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
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime)override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:

	
	
	
	
	

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* Wheels;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* Buttons;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* Wheel_Rolls;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* Pallete;
    	

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* Pallete2;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class  USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class  UCameraComponent* Camera;

	void MoveForward(const struct FInputActionValue& Value);
	void MoveRight(const struct FInputActionValue& Value);
	
	UPROPERTY(EditAnywhere, Category = "Components")
	float MovementSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Components")
	float TurnSpeed = 25.0f;


	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* TruckMappingContext;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveForwardAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveRightAction;

};
