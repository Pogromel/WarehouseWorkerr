// Parcel.cpp

#include "Parcel.h"
#include "WorkerCharacter.h"

AParcel::AParcel()
{
	// Constructor implementation
	PrimaryActorTick.bCanEverTick = true;
}

void AParcel::BeginPlay()
{
	Super::BeginPlay();
}

void AParcel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AParcel::Pickup(AWorkerCharacter* Character)
{
	// Attach the parcel to the character's holding component
	if (Character && Character->HoldingComponent)
	{
		SetActorEnableCollision(false); // Disable collision while the parcel is being held
		SetActorHiddenInGame(true); // Hide the parcel while it's being held
		AttachToComponent(Character->HoldingComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

		// Store a reference to the holding character
		HoldingCharacter = Character;
	}
}

void AParcel::Drop()
{
	// Detach the parcel from the character's holding component
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SetActorEnableCollision(true); // Enable collision after the parcel is dropped
	SetActorHiddenInGame(false); // Show the parcel again after it's dropped
}
