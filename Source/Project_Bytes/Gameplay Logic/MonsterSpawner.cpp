// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterSpawner.h"
#include "Public/TimerManager.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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
	// Count down greater than zero
	if (CountDownTimer > 0)			
	{
		// Decrease timer by 1
		--CountDownTimer;			
	}
	// If timer is equal to zero check if timerhandler is still going
	else if (GetWorldTimerManager().IsTimerActive(CountDownTimerHandler))	
	{
		// Stop calling count down timer
		GetWorldTimerManager().ClearTimer(CountDownTimerHandler);

		// Reset
		TimerOn = false;

		// First time called?
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
	// Setting indicator on
	TimerOn = true;

	// First time?
	if (!GetReady)
	{
		// Not first time then Wave cleared timer should be displayed
		WaveCleared = true;

		// Setting timer length
		CountDownTimer = 30;
	}

	// Calling decrease Timer by 1 per second
	GetWorldTimerManager().SetTimer(CountDownTimerHandler, this, &AMonsterSpawner::DecreaseCountDownTimer, 1.0f, true);

	return;
}
