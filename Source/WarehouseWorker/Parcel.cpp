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
	
}

void AParcel::Drop()
{
	// Detach the parcel from the character's holding component
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SetActorEnableCollision(true); // Enable collision after the parcel is dropped
	SetActorHiddenInGame(false); // Show the parcel again after it's dropped
}
