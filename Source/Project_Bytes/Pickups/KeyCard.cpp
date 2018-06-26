// Fill out your copyright notice in the Description page of Project Settings.

#include "KeyCard.h"

// Sets default values
AKeyCard::AKeyCard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AKeyCard::BeginPlay()
{
	Super::BeginPlay();

	// Starting life span
	GetWorldTimerManager().SetTimer(LifeSpanTimerHandle, this, &AKeyCard::DestroyActor, LifeSpan, true);
}

// Called every frame
void AKeyCard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeyCard::ProcessPickupEvent(AExterminatorMannequin * Player)
{
	// Mandatory null pointer check
	if (Player)
	{
		// Try To Increase Health
		if (Player->PickupKeycard())
		{
			// Successful

			// Destroy actor because pickup has been picked up
			DestroyActor();
		}
	}

	return;
}

void AKeyCard::DestroyActor()
{

	// Has Actor been called for destruction yet?
	if (!AKeyCard::IsPendingKill())
	{
		Super::DestroyActor();

		// Destroy actor
		AKeyCard::Destroy();
	}

	return;
}

