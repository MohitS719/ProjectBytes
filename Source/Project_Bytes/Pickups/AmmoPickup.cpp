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
	
	// Starting life span
	GetWorldTimerManager().SetTimer(LifeSpanTimerHandle, this, &AAmmoPickup::DestroyActor, LifeSpan, true);
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

void AAmmoPickup::ProcessPickupEvent(AExterminatorMannequin * Player, USoundBase *SoundSuccess, USoundBase *SoundFailed)
{
	// Mandatory null pointer check
	if (Player && SoundSuccess && SoundFailed)
	{
		PlayerReference = Player;

		// Try To Increase Ammo
		if (PlayerReference->CurrentWeapon->IncreaseAmmo(10))	
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
			PlayerReference->CurrentWeapon->bDisplayAmmoFull = true;

			PlayerReference->Indicator = 2;

			// Display indicator for sometime
			GetWorldTimerManager().SetTimer(IndicatorTimerHandle, this, &AAmmoPickup::TurnOffIndicator, IndicatorLifeSpan, true);
		}
	}

	return;
}

/*
	Private function for handling deactivation of indicators and 
	Destruction of actor
*/

void AAmmoPickup::TurnOffIndicator()
{
	// Turn of indicator
	PlayerReference->CurrentWeapon->bDisplayAmmoFull = false;

	PlayerReference->Indicator = 0;

	Super::TurnOffIndicator();

	return;
}

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
