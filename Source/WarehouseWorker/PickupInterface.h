#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickupInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPickupInterface : public UInterface
{
	GENERATED_BODY()
};

class WAREHOUSEWORKER_API IPickupInterface
{
	GENERATED_BODY()

public:
	// Define pure virtual functions for pickup and drop actions
	virtual void Pickup(class AWorkerCharacter* Character) = 0;
	virtual void Drop() = 0;
};
