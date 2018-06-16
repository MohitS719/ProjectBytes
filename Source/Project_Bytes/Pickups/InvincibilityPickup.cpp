// Fill out your copyright notice in the Description page of Project Settings.

#include "InvincibilityPickup.h"


// Sets default values
AInvincibilityPickup::AInvincibilityPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AInvincibilityPickup::BeginPlay()
{
	Super::BeginPlay();

	// Starting life span
	GetWorldTimerManager().SetTimer(LifeSpanTimerHandle, this, &AInvincibilityPickup::DestroyActor, LifeSpan, true);
}

// Called every frame
void AInvincibilityPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInvincibilityPickup::ProcessPickupEvent(AExterminatorMannequin * Player, USoundBase *SoundSuccess, USoundBase *SoundFailed)
{
	// Mandatory null pointer check
	if (Player && SoundSuccess && SoundFailed)
	{
		PlayerReference = Player;

		// Try To make player invincible
		if (PlayerReference->PickUpInvincibility())
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
			PlayerReference->bInvincibilityPickupFull = true;

			// Display indicator for sometime
			GetWorldTimerManager().SetTimer(IndicatorTimerHandle, this, &AInvincibilityPickup::TurnOffIndicator, IndicatorLifeSpan, true);
		}
	}

	return;
}

void AInvincibilityPickup::TurnOffIndicator()
{
	// Turn of indicator
	PlayerReference->bInvincibilityPickupFull = false;
	
	Super::TurnOffIndicator();

	return;
}

void AInvincibilityPickup::DestroyActor()
{
	// Has Actor been called for destruction yet?
	if (!AInvincibilityPickup::IsPendingKill())
	{
		Super::DestroyActor();

		// Destroy actor
		AInvincibilityPickup::Destroy();
	}

	return;
}
