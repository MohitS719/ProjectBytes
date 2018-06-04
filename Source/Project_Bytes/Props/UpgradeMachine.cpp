// Fill out your copyright notice in the Description page of Project Settings.

#include "UpgradeMachine.h"

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

	// Getting buyers weapon reference
	this->ShotgunReference = PlayerReference->Shotgun;
	this->PistolReference = PlayerReference->Pistol;
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

/*
	Upgrade Machine Purchase mechanisms.
	Include 2 step verification.
	Step 1. Check for player reference and Weapon reference. If NOT NULL Proceed.
	Step 2. Check Purchase criteria. Meaning, if player has enough tokens.
*/

bool AUpgradeMachine::AmmoCapacityIncrease()
{
	// Mandatory Null pointer check
	if (PlayerReference && ShotgunReference)
	{
		// Purchase criteria check
		if (PlayerReference->Tokens >= AmmoCapacityPrice)
		{
			// Performing Upgrade
			ShotgunReference->MaxAmmo += 10;					
		
			// Deduct Price
			PlayerReference->Tokens -= AmmoCapacityPrice;		

			// Increasing Price of Upgrade
			AmmoCapacityPrice += 10;

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

bool AUpgradeMachine::DamageIncrease()
{
	// Mandatory Null pointer check
	if (PlayerReference && ShotgunReference)
	{
		// Purchase criteria check
		if (PlayerReference->Tokens >= DamageIncreasePrice)
		{
			// Performing Upgrade
			ShotgunReference->WeaponDamage += 5;				

			// Deduct Price
			PlayerReference->Tokens -= DamageIncreasePrice;		

			// Increasing Price of Upgrade
			DamageIncreasePrice += 10;

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

			// Deduct Price
			PlayerReference->Tokens -= HealthCapacityPrice;		

			// Increasing Price of Upgrade
			HealthCapacityPrice += 10;

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

bool AUpgradeMachine::RefillAmmo()
{
	// Mandatory Null pointer check
	if (PlayerReference && ShotgunReference)
	{
		// Purchase criteria check
		if ( (PlayerReference->Tokens >= RefillAmmoPrice) && (ShotgunReference->Ammo < ShotgunReference->MaxAmmo) )
		{
			// Performing Upgrade
			PlayerReference->Shotgun->Ammo = PlayerReference->Shotgun->MaxAmmo;	

			// Deduct Price
			PlayerReference->Tokens -= RefillAmmoPrice;				

			// Increasing Price of Upgrade
			++RefillAmmoPrice;

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

bool AUpgradeMachine::RefillHealth()
{
	// Mandatory Null pointer check
	if (PlayerReference)
	{
		// Purchase criteria check
		if ( (PlayerReference->Tokens >= RefillHealthPrice) && (PlayerReference->Health < PlayerReference->MaxHealth) )
		{
			// Performing Upgrade
			PlayerReference->Health = PlayerReference->MaxHealth;			

			// Deduct Price
			PlayerReference->Tokens -= RefillHealthPrice;		

			// Increasing Price of Upgrade
			++RefillHealthPrice;

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

