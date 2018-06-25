// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Public/TimerManager.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "../ExterminatorCharacter/ExterminatorMannequin.h"
#include "PickUpProperties.generated.h"

UCLASS()
class PROJECT_BYTES_API APickUpProperties : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpProperties();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Life Span. How long is the pick up going to remain in the world?
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pickup Details")
	float LifeSpan = 10.0f;

	// Indicator life span. How long is the indicator going to remain active?
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pickup Details")
	float IndicatorLifeSpan = 2.0f;

	// Sounds for the picup
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pickup Sound Details")
	USoundBase * SoundSuccess; 

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pickup Sound Details")
	USoundBase * SoundFailed;

protected:

	// Player Reference
	AExterminatorMannequin * PlayerReference;

	// Process pickup event
	virtual void ProcessPickupEvent(AExterminatorMannequin * Player);

	// Destroy Actor when life span expires
	virtual void DestroyActor();

	// Turn off Indicator Display
	virtual void TurnOffIndicator();

	// Timer Handle for Health full indicator
	FTimerHandle IndicatorTimerHandle;

	// Life span of pickup
	FTimerHandle LifeSpanTimerHandle;
	
};
