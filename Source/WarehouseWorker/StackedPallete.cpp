// Fill out your copyright notice in the Description page of Project Settings.


#include "StackedPallete.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

// Sets default values
AStackedPallete::AStackedPallete()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
	RootComponent = VisualMesh;

}

// Called when the game starts or when spawned
void AStackedPallete::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStackedPallete::GiveBoxToPlayer(AActor* Player)
{
	if (!BoxBlueprint) return;

	AActor* NewBox = GetWorld()->SpawnActor<AActor>(BoxBlueprint, GetActorLocation(), GetActorRotation());
	if (NewBox)
	{
		NewBox->AttachToActor(Player, FAttachmentTransformRules::KeepWorldTransform);
		
	}
}


