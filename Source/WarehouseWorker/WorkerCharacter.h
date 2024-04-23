

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


UCLASS()
class WAREHOUSEWORKER_API AWorkerCharacter : public ACharacter
{
	GENERATED_BODY()

	

public:
	AWorkerCharacter();




protected:
	virtual void BeginPlay() override;

	//Movement and pickup/drop
	
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

	//Post Process
	UPROPERTY(EditAnywhere)
	UPrimitiveComponent* FloorSplashPlane;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* ScreenWaterSplashMaterial;

	UMaterialInstanceDynamic* PostProcessMaterialInstance;




	//voids

	void SetPostProcessDynamicMaterialInstance();
	void ActivatePostProcessEffect();
	void OnFloorSplashPlaneCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void PickUp(const FInputActionValue& Value);
	void Drop(const FInputActionValue& Value);

	//Timer

	int32 TotalSecounds;
	int32 RemainingSecounds;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
	UTextBlock* MinutesTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
	UTextBlock* SecoundsTextBlock;

	void StartTimer();
	void UpdateTimerDisplay();
	FString FormatTime(int32 TimeInSecounds);

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
};