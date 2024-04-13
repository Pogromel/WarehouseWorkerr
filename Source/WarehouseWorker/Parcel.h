#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Parcel.generated.h"

class AWorkerCharacter; // Forward declaration of AWorkerCharacter

UCLASS()
class WAREHOUSEWORKER_API AParcel : public AActor
{
	GENERATED_BODY()

public:
	AParcel();


protected:
	virtual void BeginPlay() override;
	
	

public:
	virtual void Tick(float DeltaTime) override;

	void Pickup(AWorkerCharacter* Character);

	void Drop();

};
