// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUpProperties.h"
#include "HealthPickUp.generated.h"

UCLASS()
class PROJECT_BYTES_API AHealthPickUp : public APickUpProperties
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Process Pickup event
	UFUNCTION(BlueprintCallable, Category = "Health Pickup Details")
	void ProcessPickupEvent(AExterminatorMannequin * Player) override;

private:

	// Destroy Actor when life span expires
	UFUNCTION()
	void DestroyActor() override;
};
