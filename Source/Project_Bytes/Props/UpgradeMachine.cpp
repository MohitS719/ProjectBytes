// Fill out your copyright notice in the Description page of Project Settings.

#include "UpgradeMachine.h"


// Sets default values
AUpgradeMachine::AUpgradeMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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


bool AUpgradeMachine::AmmoCapacityIncrease(AExterminatorMannequin *PlayerReference)
{
	if (PlayerReference->Tokens >= AmmoCapacityPrice)
	{
		PlayerReference->MaxAmmo += 10;						// Performing Upgrade

		PlayerReference->Tokens -= AmmoCapacityPrice;		// Deduct Price

		AmmoCapacityPrice += 10;

		return true;										// Purchase Successful
	}

	return false;											// Purchase Failed
}

bool AUpgradeMachine::DamageIncrease(AExterminatorMannequin *PlayerReference)
{
	if (PlayerReference->Tokens >= DamageIncreasePrice)
	{
		PlayerReference->WeaponDamage += 5;					// Performing Upgrade

		PlayerReference->Tokens -= DamageIncreasePrice;		// Deduct Price

		DamageIncreasePrice += 10;

		return true;										// Purchase Successful
	}

	return false;											// Purchase Failed
}

bool AUpgradeMachine::HealthCapacityIncrease(AExterminatorMannequin *PlayerReference)
{
	if (PlayerReference->Tokens >= HealthCapacityPrice)
	{
		PlayerReference->MaxHealth += 10.0;					// Performing Upgrade

		PlayerReference->Tokens -= HealthCapacityPrice;		// Deduct Price

		HealthCapacityPrice += 10;

		return true;										// Purchase Successful
	}

	return false;											// Purchase Failed
}

bool AUpgradeMachine::RefillAmmo(AExterminatorMannequin *PlayerReference)
{
	if (PlayerReference->Tokens >= RefillAmmoPrice && PlayerReference->Health < PlayerReference->MaxHealth)
	{
		PlayerReference->Health = PlayerReference->MaxHealth;	// Performing Upgrade

		PlayerReference->Tokens -= RefillAmmoPrice;				// Deduct Price

		++RefillAmmoPrice;

		return true;											// Purchase Successful
	}

	return false;												// Purchase Failed
}

bool AUpgradeMachine::RefillHealth(AExterminatorMannequin *PlayerReference)
{
	if (PlayerReference->Tokens >= RefillHealthPrice && PlayerReference->Ammo < PlayerReference->MaxAmmo)
	{
		PlayerReference->Ammo = PlayerReference->MaxAmmo;	// Performing Upgrade

		PlayerReference->Tokens -= RefillHealthPrice;		// Deduct Price

		++RefillHealthPrice;

		return true;										// Purchase Successful
	}

	return false;											// Purchase Failed
}

