// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "StackedPallete.generated.h"

UCLASS()
class WAREHOUSEWORKER_API AStackedPallete : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStackedPallete();

	void GiveBoxToPlayer(AActor* Player);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void SpawnBox();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Box")
	TSubclassOf<AActor> BoxBlueprint;

};
