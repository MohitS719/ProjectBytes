// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUpProperties.h"
#include "AmmoPickup.generated.h"

UCLASS()
class PROJECT_BYTES_API AAmmoPickup : public APickUpProperties
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoPickup();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Process Pickup event
	UFUNCTION(BlueprintCallable, Category = "Ammo Pickup Details")
	void ProcessPickupEvent(AExterminatorMannequin * Player) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// Destroy Actor when life span expires
	UFUNCTION()
	void DestroyActor() override;

	// Turn off Indicator Display
	UFUNCTION()
	void TurnOffIndicator() override;
};
