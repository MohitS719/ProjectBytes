// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterSpawner.h"

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
	// Count down greater than zero and is player outside the upgrade machine?
	if (CountDownTimer > 0 && !(UpgradeMachineReference->InUpgradeMachine))
	{
		// Decrease timer by 1
		--CountDownTimer;			
	}
	// If timer is equal to zero check if timerhandler is still going
	else if (CountDownTimer <= 0)
	{
		if (GetWorldTimerManager().IsTimerActive(CountDownTimerHandler))
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
	}

	return;
}

void AMonsterSpawner::Initialization(AUpgradeMachine * UpgradeMachine)
{
	UpgradeMachineReference = UpgradeMachine;

	return;
}

void AMonsterSpawner::PrepareForNextWave()
{
	// Increase wave number
	++WaveNumber;

	// Reset count down timer
	CountDownTimer = 30;

	// Is Wave number even or greater than 10?
	if ( (WaveNumber & 1) || (WaveNumber > 10) )
	{
		MonsterHealth += 10;
	}
	else
	{
		MonsterCount += WaveNumber;
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
