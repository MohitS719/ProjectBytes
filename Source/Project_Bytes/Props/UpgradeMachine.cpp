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
	this->PlayerReference = PlayerReference;
	this->ShotgunReference = PlayerReference->Shotgun;
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


bool AUpgradeMachine::AmmoCapacityIncrease()
{
	if (PlayerReference == nullptr || ShotgunReference == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pointer Error From Upgrade Machine"))

		return false;
	}

	if (PlayerReference->Tokens >= AmmoCapacityPrice)
	{
		ShotgunReference->MaxAmmo += 10;					// Performing Upgrade
		
		PlayerReference->Tokens -= AmmoCapacityPrice;		// Deduct Price

		AmmoCapacityPrice += 10;

		return true;										// Purchase Successful
	}

	return false;											// Purchase Failed
}

bool AUpgradeMachine::DamageIncrease()
{
	if (PlayerReference == nullptr || ShotgunReference == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pointer Error From Upgrade Machine"))

			return false;
	}

	if (PlayerReference->Tokens >= DamageIncreasePrice)
	{
		ShotgunReference->WeaponDamage += 5;				// Performing Upgrade

		PlayerReference->Tokens -= DamageIncreasePrice;		// Deduct Price

		DamageIncreasePrice += 10;

		return true;										// Purchase Successful
	}

	return false;											// Purchase Failed
}

bool AUpgradeMachine::HealthCapacityIncrease()
{
	if (PlayerReference == nullptr || ShotgunReference == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pointer Error From Upgrade Machine"))

			return false;
	}

	if (PlayerReference->Tokens >= HealthCapacityPrice)
	{
		PlayerReference->MaxHealth += 10.0;					// Performing Upgrade

		PlayerReference->Tokens -= HealthCapacityPrice;		// Deduct Price

		HealthCapacityPrice += 10;

		return true;										// Purchase Successful
	}

	return false;											// Purchase Failed
}

bool AUpgradeMachine::RefillAmmo()
{
	if (PlayerReference == nullptr || ShotgunReference == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pointer Error From Upgrade Machine"))

			return false;
	}

	if (PlayerReference->Tokens >= RefillAmmoPrice && PlayerReference->Health < PlayerReference->MaxHealth)
	{
		PlayerReference->Health = PlayerReference->MaxHealth;	// Performing Upgrade

		PlayerReference->Tokens -= RefillAmmoPrice;				// Deduct Price

		++RefillAmmoPrice;

		return true;											// Purchase Successful
	}

	return false;												// Purchase Failed
}

bool AUpgradeMachine::RefillHealth()
{
	if (PlayerReference == nullptr || ShotgunReference == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pointer Error From Upgrade Machine"))

			return false;
	}

	if (PlayerReference->Tokens >= RefillHealthPrice && ShotgunReference->Ammo < ShotgunReference->MaxAmmo)
	{
		PlayerReference->Shotgun->Ammo = PlayerReference->Shotgun->MaxAmmo;	// Performing Upgrade

		PlayerReference->Tokens -= RefillHealthPrice;		// Deduct Price

		++RefillHealthPrice;

		return true;										// Purchase Successful
	}

	return false;											// Purchase Failed
}

