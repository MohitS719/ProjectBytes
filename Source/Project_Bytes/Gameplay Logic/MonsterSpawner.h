// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawner.generated.h"

UCLASS()
class PROJECT_BYTES_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterSpawner();

	/*
		Spawner essential variables
	*/

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawner Details")
	int WaveNumber = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawner Details")
	int MonsterCount = 2;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawner Details")
	int CountDownTimer = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawner Details")
	float MonsterHealth = 25;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawner Details")
	bool TimerOn = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawner Details")
	bool GetReady = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawner Details")
	bool WaveCleared = false;

	UFUNCTION(BlueprintCallable, Category = "Character Details")
	void CallTimer();

private:
	UFUNCTION()
	void DecreaseCountDownTimer();

	// Timer Handle for Count Down Timer
	FTimerHandle CountDownTimerHandler;

	// Timer Handle for Stamina depletion
	// FTimerHandle StaminaDepleteTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
