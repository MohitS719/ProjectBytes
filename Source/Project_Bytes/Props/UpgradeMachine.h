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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															/************************************************************************
															*						FUNDAMENTAL LOGIC START							*
															*				MEMBER FUNCTIONS AND MEMBER VARIABLES					*
															************************************************************************/
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

public:
							/**	Upgrade Prices	*/

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Upgrade Price Details")
	int AmmoCapacityPrice = 5;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Upgrade Price Details")
	int DamageIncreasePrice = 5;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Upgrade Price Details")
	int HealthCapacityPrice = 5;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Upgrade Price Details")
	int RefillHealthPrice = 3;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Upgrade Price Details")
	int RefillAmmoPrice = 3;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Upgrade Price Details")
	int StaminaCapacityPrice = 5;

					/**	Increase rate of Upgrade Prices */

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Price increase rate")
	int IncreaseAmmoCapacityPrice = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Price increase rate")
	int IncreaseDamageIncreasePrice = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Price increase rate")
	int IncreaseHealthCapacityPrice = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Price increase rate")
	int IncreaseRefillHealthPrice = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Price increase rate")
	int IncreaseRefillAmmoPrice = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Price increase rate")
	int IncreaseStaminaCapacityPrice = 10;

							/** Upgrade Functions */

						/** Character related upgrades */

	UFUNCTION(BlueprintCallable, Category = "Upgrade Purchase Function")
	bool HealthCapacityIncrease();

	UFUNCTION(BlueprintCallable, Category = "Upgrade Purchase Function")
	bool RefillHealth();

	UFUNCTION(BlueprintCallable, Category = "Upgrade Purchase Function")
	bool StaminaCapacityIncrease();

						/** Pistol related upgrades */
	
	UFUNCTION(BlueprintCallable, Category = "Upgrade Purchase Function")
	bool PistolAmmoCapacityIncrease();

	UFUNCTION(BlueprintCallable, Category = "Upgrade Purchase Function")
	bool PistolDamageIncrease();

						/** Shotgun related upgrades */

	UFUNCTION(BlueprintCallable, Category = "Upgrade Purchase Function")
	bool ShotgunAmmoCapacityIncrease();

	UFUNCTION(BlueprintCallable, Category = "Upgrade Purchase Function")
	bool ShotgunDamageIncrease();

					/** Common Weapon related upgrades */

	UFUNCTION(BlueprintCallable, Category = "Upgrade Purchase Function")
	bool RefillAmmo();


private:
				/** References used for performing upgrades */

	AExterminatorMannequin * PlayerReference;		

														/************************************************************************
														*					UPGRADE FUNCTIONALITY LOGIC END						*
														*				 MEMBER FUNCTIONS AND MEMBER VARIABLES					*
														************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

};
