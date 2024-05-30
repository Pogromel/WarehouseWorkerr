// Fill out your copyright notice in the Description page of Project Settings.


#include "StackedPallete.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "WorkerCharacter.h"

// Sets default values
AStackedPallete::AStackedPallete()
{
 	
	

}

// Called when the game starts or when spawned
void AStackedPallete::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStackedPallete::SpawnBoxInHands(AWorkerCharacter* WorkerCharacter)
{
	if (WorkerCharacter)
	{
		WorkerCharacter->SpawnBoxInHands();
	}
}


