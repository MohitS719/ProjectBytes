// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpProperties.h"


// Sets default values
APickUpProperties::APickUpProperties()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void APickUpProperties::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUpProperties::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUpProperties::DestroyActor()
{
	// Nope. Then check if the timer is active
	if (GetWorldTimerManager().IsTimerActive(LifeSpanTimerHandle))
	{
		// Ending life span
		GetWorldTimerManager().ClearTimer(LifeSpanTimerHandle);
	}
	
	// UE_LOG(LogTemp, Warning, TEXT("Destroyed from Super!"))

	return;
}


void APickUpProperties::ProcessPickupEvent(AExterminatorMannequin * Player)
{
	return;
}
