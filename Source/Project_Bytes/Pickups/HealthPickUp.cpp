// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthPickUp.h"

// Sets default values
AHealthPickUp::AHealthPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AHealthPickUp::BeginPlay()
{
	Super::BeginPlay();

	if (bDestructible)
	{
		// Starting life span
		GetWorldTimerManager().SetTimer(LifeSpanTimerHandle, this, &AHealthPickUp::DestroyActor, LifeSpan, true);
	}
}

// Called every frame
void AHealthPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*
	Main function that interacts with the outside world.
	Performs pickup checks and calls appropriate increase function
*/

void AHealthPickUp::ProcessPickupEvent(AExterminatorMannequin * Player)
{
	// Mandatory null pointer check
	if (Player)
	{
		// Try To Increase Health
		if (Player->PickupHealth())
		{
			// Destroy actor because pickup has been picked up
			DestroyActor();
		}
	}

	return;
}

/*
	Private function for handling deactivation of indicators and
	Destruction of actor
*/

void AHealthPickUp::DestroyActor()
{
	
	// Has Actor been called for destruction yet?
	if (!AHealthPickUp::IsPendingKill())
	{
		Super::DestroyActor();

		// Destroy actor
		AHealthPickUp::Destroy();
	}

	return;
}
