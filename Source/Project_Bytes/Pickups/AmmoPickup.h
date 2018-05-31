// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../ExterminatorCharacter/ExterminatorMannequin.h"
#include "AmmoPickup.generated.h"

UCLASS()
class PROJECT_BYTES_API AAmmoPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoPickup();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Process Pickup event
	UFUNCTION(BlueprintCallable, Category = "Ammo Pickup Details")
	void ProcessPickupEvent(AExterminatorMannequin * Player, USoundBase *SoundSuccess, USoundBase *SoundFailed);

	// Life Span
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ammo Pickup Details")
	float LifeSpan = 10.0f;

	// Indicator life span
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ammo Pickup Details")
	float IndicatorLifeSpan = 2.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// Player Reference
	AExterminatorMannequin * PlayerReference;

	// Turn off Indicator Display
	UFUNCTION()
	void TurnOffIndicator();

	// Destroy Actor when life span expires
	UFUNCTION()
	void DestroyActor();

	// Timer Handle for Ammo full indicator
	FTimerHandle AmmoFullTimerHandle;

	// Life span of pickup
	FTimerHandle LifeSpanTimerHandle;
};
