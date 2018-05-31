// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../ExterminatorCharacter/ExterminatorMannequin.h"
#include "../Gun.h"
#include "UpgradeMachine.generated.h"

#define UPGRADES 5

UCLASS()
class PROJECT_BYTES_API AUpgradeMachine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUpgradeMachine();

	// Initialize the player and Gun pointers with the real world ones
	UFUNCTION(BlueprintCallable, Category = "Upgrade Machine")
	void Initialize(AExterminatorMannequin *PlayerReference);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
		Upgrade Prices
	*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Upgrade Price Details")
	int AmmoCapacityPrice = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Upgrade Price Details")
	int DamageIncreasePrice = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Upgrade Price Details")
	int HealthCapacityPrice = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Upgrade Price Details")
	int RefillHealthPrice = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Upgrade Price Details")
	int RefillAmmoPrice = 3;

	// Purchase using Player Token
	
	/*
		Upgrade Functions
	*/

	UFUNCTION(BlueprintCallable, Category = "Upgrade Purchase Function")
	bool AmmoCapacityIncrease();

	UFUNCTION(BlueprintCallable, Category = "Upgrade Purchase Function")
	bool DamageIncrease();

	UFUNCTION(BlueprintCallable, Category = "Upgrade Purchase Function")
	bool HealthCapacityIncrease();

	UFUNCTION(BlueprintCallable, Category = "Upgrade Purchase Function")
	bool RefillAmmo();

	UFUNCTION(BlueprintCallable, Category = "Upgrade Purchase Function")
	bool RefillHealth();
	
private:
	// Reference of buyer
	AExterminatorMannequin * PlayerReference;

	// Reference of player's weapon
	AGun *ShotgunReference;
};
