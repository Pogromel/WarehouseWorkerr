// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pickup.h"
#include "WorkerCharacter.generated.h"

UCLASS()
class WAREHOUSEWORKER_API AWorkerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class USceneComponent* HoldingComponent;

	

public:
	// Sets default values for this character's properties
	AWorkerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	class APickup* CurrentItem;


	bool bCanMove;
	bool bHoldingItem;

	FVector HoldingComp;

	FVector Start;
	FVector ForwardVector;
	FVector End;

	FHitResult Hit;

	FComponentQueryParams DefaultComponentQueryParams;
	FCollisionResponseParams DefaultResponseParams;
	

private:
	void MovingForward(float AxisValue); // passes value from input system in this case W or S would be 1 or -1

	void OnAction();
	void OnActionReleased();
	
	void LookUp(float AxisValue); // passes value from input system in this case Mouse Up or Mouse Down would be 1 or -1

	void MovingSideways(float AxisValue);

	void LookSideways(float AxisValue);

	void ToggleMovement();
	void ToggleItemPickup();

};
