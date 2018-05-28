// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../ExterminatorCharacter/ExterminatorMannequin.h"
#include "UpgradeMachine.generated.h"

#define UPGRADES 5

UCLASS()
class PROJECT_BYTES_API AUpgradeMachine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUpgradeMachine();

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

	UFUNCTION(BlueprintCallable, Category = "Upgrade Machine")
	bool AmmoCapacityIncrease(AExterminatorMannequin *PlayerReference);

	UFUNCTION(BlueprintCallable, Category = "Upgrade Machine")
	bool DamageIncrease(AExterminatorMannequin *PlayerReference);

	UFUNCTION(BlueprintCallable, Category = "Upgrade Machine")
	bool HealthCapacityIncrease(AExterminatorMannequin *PlayerReference);

	UFUNCTION(BlueprintCallable, Category = "Upgrade Machine")
	bool RefillAmmo(AExterminatorMannequin *PlayerReference);

	UFUNCTION(BlueprintCallable, Category = "Upgrade Machine")
	bool RefillHealth(AExterminatorMannequin *PlayerReference);


};
