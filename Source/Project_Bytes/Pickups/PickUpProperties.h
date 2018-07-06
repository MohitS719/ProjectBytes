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
	float LifeSpan = 60.0f;

	// Will it be distructible?
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pickup Details")
	bool bDestructible = true;

protected:
	// Process pickup event
	virtual void ProcessPickupEvent(AExterminatorMannequin * Player);

	// Destroy Actor when life span expires
	virtual void DestroyActor();

	// Life span of pickup
	FTimerHandle LifeSpanTimerHandle;
	
};
