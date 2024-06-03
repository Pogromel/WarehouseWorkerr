#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StackedPallete.generated.h"

// Forward declaration of AWorkerCharacter
class AWorkerCharacter;

UCLASS()
class WAREHOUSEWORKER_API AStackedPallete : public AActor
{
    GENERATED_BODY()
    
public:    
    // Sets default values for this actor's properties
    AStackedPallete();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Remove the Tick method declaration if not needed
    // virtual void Tick(float DeltaTime) override;

    void SpawnBoxInHands(AWorkerCharacter* WorkerCharacter);
};
