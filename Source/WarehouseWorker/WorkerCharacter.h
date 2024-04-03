

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

	UPROPERTY(EditAnywhere)
	class USceneComponent* HoldingComponent;


protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;
	
	
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

	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }

};
