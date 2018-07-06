// Fill out your copyright notice in the Description page of Project Settings.

#include "UpgradeMachine.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																/************************************************************************
																*						FUNDAMENTAL LOGIC START							*
																*				MEMBER FUNCTIONS AND MEMBER VARIABLES					*
																************************************************************************/

// Sets default values
AUpgradeMachine::AUpgradeMachine()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AUpgradeMachine::Initialize(AExterminatorMannequin * PlayerReference)
{
	// Getting buyer reference
	this->PlayerReference = PlayerReference;
}

// Called when the game starts or when spawned
void AUpgradeMachine::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AUpgradeMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


																/************************************************************************
																*						FUNDAMENTAL LOGIC END							*
																*				MEMBER FUNCTIONS AND MEMBER VARIABLES					*
																************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																/************************************************************************
																*					UPGRADE FUNCTIONALITY LOGIC START					*
																*				 MEMBER FUNCTIONS AND MEMBER VARIABLES					*
																************************************************************************/

																/**
																*		Upgrade Machine Purchase mechanisms.
																*		Include 2 step verification.
																*		Step 1. Check for player reference and Weapon reference. If NOT NULL Proceed.
																*		Step 2. Check Purchase criteria. Meaning, if player has enough tokens.
																*/



				/** Character related upgrades */

// Increases the maximum health capacity of player.
bool AUpgradeMachine::HealthCapacityIncrease()
{
	// Mandatory Null pointer check
	if (PlayerReference)
	{
		// Purchase criteria check
		if (PlayerReference->Tokens >= HealthCapacityPrice)
		{
			// Performing Upgrade
			PlayerReference->MaxHealth += 10.0;

			// Health ratio calculation
			PlayerReference->HealthRatio = (PlayerReference->Health / PlayerReference->MaxHealth);

			// Deduct Price
			PlayerReference->Tokens -= HealthCapacityPrice;

			// Increasing Price of Upgrade
			HealthCapacityPrice += IncreaseHealthCapacityPrice;

			// Purchase Successful
			return true;
		}
	}
	else
	{
		// Show error message
		UE_LOG(LogTemp, Warning, TEXT("Pointer Error From Upgrade Machine"))
	}

	// Purchase Failed
	return false;
}

// Refills the player's health and sets it equal to max health.
bool AUpgradeMachine::RefillHealth()
{
	// Mandatory Null pointer check
	if (PlayerReference)
	{
		// Purchase criteria check
		if ((PlayerReference->Tokens >= RefillHealthPrice) && (PlayerReference->Health < PlayerReference->MaxHealth))
		{
			// Performing Upgrade
			PlayerReference->Health = PlayerReference->MaxHealth;

			// Health ratio calculation
			PlayerReference->HealthRatio = (PlayerReference->Health / PlayerReference->MaxHealth);

			// Deduct Price
			PlayerReference->Tokens -= RefillHealthPrice;

			// Increasing Price of Upgrade
			RefillHealthPrice += IncreaseRefillHealthPrice;

			// Purchase Successful
			return true;
		}
	}
	else
	{
		// Show error message
		UE_LOG(LogTemp, Warning, TEXT("Pointer Error From Upgrade Machine"))
	}

	// Purchase Failed
	return false;
}

// Increases maximum stamina capacity of player
bool AUpgradeMachine::StaminaCapacityIncrease()
{
	// Mandatory Null pointer check
	if (PlayerReference)
	{
		// Purchase criteria check
		if (PlayerReference->Tokens >= StaminaCapacityPrice)
		{
			// Performing Upgrade
			PlayerReference->MaxStamina += 2.0;

			// Stamina ratio calculation
			PlayerReference->StaminaRatio = (PlayerReference->Stamina / PlayerReference->MaxStamina);

			// Deduct Price
			PlayerReference->Tokens -= StaminaCapacityPrice;

			// Increasing Price of Upgrade
			StaminaCapacityPrice += IncreaseStaminaCapacityPrice;

			// Purchase Successful
			return true;
		}
	}
	else
	{
		// Show error message
		UE_LOG(LogTemp, Warning, TEXT("Pointer Error From Upgrade Machine"))
	}

	// Purchase Failed
	return false;
}

				/** Pistol related upgrades */

// Increases the maximum ammo of pistol carriable by the player.
bool AUpgradeMachine::PistolAmmoCapacityIncrease()
{
	// Mandatory Null pointer check
	if (PlayerReference)
	{
		// Purchase criteria check
		if (PlayerReference->Tokens >= AmmoCapacityPrice)
		{
			// Performing Upgrade
			PlayerReference->Pistol->MaxAmmo += 10;

			// Deduct Price
			PlayerReference->Tokens -= AmmoCapacityPrice;

			// Increasing Price of Upgrade
			AmmoCapacityPrice += IncreaseAmmoCapacityPrice;

			// Purchase Successful
			return true;
		}
	}
	else
	{
		// Show error message
		UE_LOG(LogTemp, Warning, TEXT("Pointer Error From Upgrade Machine"))
	}

	// Purchase Failed
	return false;
}

// Increases the damage done by the pistol.
bool AUpgradeMachine::PistolDamageIncrease()
{
	// Mandatory Null pointer check
	if (PlayerReference)
	{
		// Purchase criteria check
		if (PlayerReference->Tokens >= DamageIncreasePrice)
		{
			// Performing Upgrade
			PlayerReference->Pistol->WeaponDamage += 5;

			// Deduct Price
			PlayerReference->Tokens -= DamageIncreasePrice;

			// Increasing Price of Upgrade
			DamageIncreasePrice += IncreaseDamageIncreasePrice;

			// Purchase Successful
			return true;
		}
	}
	else
	{
		// Show error message
		UE_LOG(LogTemp, Warning, TEXT("Pointer Error From Upgrade Machine"))
	}

	// Purchase Failed
	return false;
}

				/** Shotgun related upgrades */

// Increases the maximum ammo of shotgun carriable by the player.
bool AUpgradeMachine::ShotgunAmmoCapacityIncrease()
{
	// Mandatory Null pointer check
	if (PlayerReference)
	{
		// Purchase criteria check
		if (PlayerReference->Tokens >= AmmoCapacityPrice)
		{
			// Performing Upgrade
			PlayerReference->Shotgun->MaxAmmo += 10;

			// Deduct Price
			PlayerReference->Tokens -= AmmoCapacityPrice;

			// Increasing Price of Upgrade
			AmmoCapacityPrice += IncreaseAmmoCapacityPrice;

			// Purchase Successful
			return true;
		}
	}
	else
	{
		// Show error message
		UE_LOG(LogTemp, Warning, TEXT("Pointer Error From Upgrade Machine"))
	}

	// Purchase Failed
	return false;
}

// Increases the damage done by the shotgun.
bool AUpgradeMachine::ShotgunDamageIncrease()
{
	// Mandatory Null pointer check
	if (PlayerReference)
	{
		// Purchase criteria check
		if (PlayerReference->Tokens >= DamageIncreasePrice)
		{
			// Performing Upgrade
			PlayerReference->Shotgun->WeaponDamage += 5;

			// Deduct Price
			PlayerReference->Tokens -= DamageIncreasePrice;

			// Increasing Price of Upgrade
			DamageIncreasePrice += IncreaseDamageIncreasePrice;

			// Purchase Successful
			return true;
		}
	}
	else
	{
		// Show error message
		UE_LOG(LogTemp, Warning, TEXT("Pointer Error From Upgrade Machine"))
	}

	// Purchase Failed
	return false;
}

			/** Common Weapon related upgrades */

// Refill ammo for all weapons.
bool AUpgradeMachine::RefillAmmo()
{
	// Mandatory Null pointer check
	if (PlayerReference)
	{
		// Purchase criteria check
		if ( (PlayerReference->Tokens >= RefillAmmoPrice) && ( (PlayerReference->Shotgun->Ammo < PlayerReference->Shotgun->MaxAmmo) || (PlayerReference->Pistol->Ammo < PlayerReference->Pistol->MaxAmmo) ) )
		{
			// Performing Upgrade
			PlayerReference->Shotgun->Ammo = PlayerReference->Shotgun->MaxAmmo;
			PlayerReference->Pistol->Ammo = PlayerReference->Pistol->MaxAmmo;

			// Deduct Price
			PlayerReference->Tokens -= RefillAmmoPrice;

			// Increasing Price of Upgrade
			RefillAmmoPrice += IncreaseRefillAmmoPrice;

			// Purchase Successful
			return true;
		}
	}
	else
	{
		// Show error message
		UE_LOG(LogTemp, Warning, TEXT("Pointer Error From Upgrade Machine"))
	}

	// Purchase Failed
	return false;
}



																/************************************************************************
																*					UPGRADE FUNCTIONALITY LOGIC END						*
																*				 MEMBER FUNCTIONS AND MEMBER VARIABLES					*
																************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////