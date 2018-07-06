// Fill out your copyright notice in the Description page of Project Settings.

#include "AmmoPickup.h"
#include "../Gun.h"

// Sets default values
AAmmoPickup::AAmmoPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AAmmoPickup::BeginPlay()
{
	Super::BeginPlay();
	
	if (bDestructible)
	{
		// Starting life span
		GetWorldTimerManager().SetTimer(LifeSpanTimerHandle, this, &AAmmoPickup::DestroyActor, LifeSpan, true);
	}
}

// Called every frame
void AAmmoPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*
	Main function that interacts with the outside world.
	Performs pickup checks and calls appropriate increase function
*/

void AAmmoPickup::ProcessPickupEvent(AExterminatorMannequin * Player)
{
	// Mandatory null pointer check
	if (Player)
	{
		// Try To Increase Ammo
		if (Player->CurrentWeapon->IncreaseAmmo(10))	
		{
			// Successful

			// Destroy actor because pickup has been picked up
			DestroyActor();
		}
		else
		{
			// Failure to pickup
			Super::ProcessPickupEvent(Player);

			// Display indicator
			Player->TurnOnIndicator(2, 2.0f);
		}
	}

	return;
}

/*
	Private function for handling deactivation of indicators and 
	Destruction of actor
*/


void AAmmoPickup::DestroyActor()
{
	// Has Actor been called for destruction yet?
	if (!AAmmoPickup::IsPendingKill())
	{
		Super::DestroyActor();

		// Destroy actor
		AAmmoPickup::Destroy();
	}

	return;
}
