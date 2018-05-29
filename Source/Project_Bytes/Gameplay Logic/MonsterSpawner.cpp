// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterSpawner.h"
#include "Public/TimerManager.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterSpawner::DecreaseCountDownTimer()
{
	if (CountDownTimer > 0)			// Count down greater than zzero
	{
		--CountDownTimer;			// Decrease timer by 1
	}
	else if (GetWorldTimerManager().IsTimerActive(CountDownTimerHandler))	// If timer is equal to zero check if timerhandler is still going
	{
		// Stop calling count down timer
		GetWorldTimerManager().ClearTimer(CountDownTimerHandler);

		// Reset
		TimerOn = false;

		if (GetReady)
		{
			GetReady = false;
		}
		else if (WaveCleared)
		{
			WaveCleared = false;
		}
	}

	return;
}

void AMonsterSpawner::CallTimer()
{
	TimerOn = true;

	if (!GetReady)
	{
		WaveCleared = true;
		CountDownTimer = 30;
	}

	// Calling decrease Timer by 1 per second
	GetWorldTimerManager().SetTimer(CountDownTimerHandler, this, &AMonsterSpawner::DecreaseCountDownTimer, 1.0f, true);

	return;
}
