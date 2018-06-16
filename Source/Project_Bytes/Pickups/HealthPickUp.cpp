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

	// Starting life span
	GetWorldTimerManager().SetTimer(LifeSpanTimerHandle, this, &AHealthPickUp::DestroyActor, LifeSpan, true);
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

void AHealthPickUp::ProcessPickupEvent(AExterminatorMannequin * Player, USoundBase *SoundSuccess, USoundBase *SoundFailed)
{
	// Mandatory null pointer check
	if (Player && SoundSuccess && SoundFailed)
	{
		PlayerReference = Player;

		// Try To Increase Health
		if (PlayerReference->Heal(10.0))
		{
			// Successful

			// Play success sound
			UGameplayStatics::PlaySoundAtLocation(PlayerReference, SoundSuccess, PlayerReference->GetActorLocation());

			// Destroy actor because pickup has been picked up
			DestroyActor();
		}
		else
		{
			// Failure to pickup

			// Play failure sound
			UGameplayStatics::PlaySoundAtLocation(PlayerReference, SoundFailed, PlayerReference->GetActorLocation());

			// Inventory full
			PlayerReference->bDisplayHealthFull = true;

			// Display indicator for sometime
			GetWorldTimerManager().SetTimer(IndicatorTimerHandle, this, &AHealthPickUp::TurnOffIndicator, IndicatorLifeSpan, true);
		}
	}

	return;
}

/*
	Private function for handling deactivation of indicators and
	Destruction of actor
*/

void AHealthPickUp::TurnOffIndicator()
{
	// Turn of indicator
	PlayerReference->bDisplayHealthFull = false;

	Super::TurnOffIndicator();

	return;
}

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
