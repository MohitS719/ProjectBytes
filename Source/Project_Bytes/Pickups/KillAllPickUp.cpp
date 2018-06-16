// Fill out your copyright notice in the Description page of Project Settings.

#include "KillAllPickUp.h"


// Sets default values
AKillAllPickUp::AKillAllPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AKillAllPickUp::BeginPlay()
{
	Super::BeginPlay();

	// Starting life span
	GetWorldTimerManager().SetTimer(LifeSpanTimerHandle, this, &AKillAllPickUp::DestroyActor, LifeSpan, true);
}

// Called every frame
void AKillAllPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKillAllPickUp::DestroyActor()
{

	// Has Actor been called for destruction yet?
	if (!AKillAllPickUp::IsPendingKill())
	{
		Super::DestroyActor();

		// Destroy actor
		AKillAllPickUp::Destroy();
	}

	return;
}

