// Fill out your copyright notice in the Description page of Project Settings.

#include "OneShotKill.h"


// Sets default values
AOneShotKill::AOneShotKill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AOneShotKill::BeginPlay()
{
	Super::BeginPlay();

	// Starting life span
	GetWorldTimerManager().SetTimer(LifeSpanTimerHandle, this, &AOneShotKill::DestroyActor, LifeSpan, true);
}

// Called every frame
void AOneShotKill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOneShotKill::DestroyActor()
{

	// Has Actor been called for destruction yet?
	if (!AOneShotKill::IsPendingKill())
	{
		Super::DestroyActor();

		// Destroy actor
		AOneShotKill::Destroy();
	}

	return;
}
