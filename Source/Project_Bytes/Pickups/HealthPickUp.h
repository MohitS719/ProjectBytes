// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../ExterminatorCharacter/ExterminatorMannequin.h"
#include "HealthPickUp.generated.h"

UCLASS()
class PROJECT_BYTES_API AHealthPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Process Pickup event
	UFUNCTION(BlueprintCallable, Category = "Health Pickup Details")
	void ProcessPickupEvent(AExterminatorMannequin * Player, USoundBase *SoundSuccess, USoundBase *SoundFailed);

	// Life Span. How long is the pick up going to remain in the world?
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health Pickup Details")
	float LifeSpan = 10.0f;

	// Indicator life span. How long is the indicator going to remain active?
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health Pickup Details")
	float IndicatorLifeSpan = 2.0f;

private:

	// Player Reference
	AExterminatorMannequin * PlayerReference;

	// Turn off Indicator Display
	UFUNCTION()
	void TurnOffIndicator();

	// Destroy Actor when life span expires
	UFUNCTION()
	void DestroyActor();

	// Timer Handle for Health full indicator
	FTimerHandle HealthFullTimerHandle;

	// Life span of pickup
	FTimerHandle LifeSpanTimerHandle;
	
};
