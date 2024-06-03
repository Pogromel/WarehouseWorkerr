#include "StackedPallete.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "WorkerCharacter.h"

// Sets default values
AStackedPallete::AStackedPallete()
{
    // PrimaryActorTick.bCanEverTick = true;  // Comment out or remove this if not needed
}

// Called when the game starts or when spawned
void AStackedPallete::BeginPlay()
{
    Super::BeginPlay();
}

// Remove the Tick method definition
/*
void AStackedPallete::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
*/

void AStackedPallete::SpawnBoxInHands(AWorkerCharacter* WorkerCharacter)
{
    if (WorkerCharacter)
    {
        WorkerCharacter->SpawnBoxInHands();
    }
}
