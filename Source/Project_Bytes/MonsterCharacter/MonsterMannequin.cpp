// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealMathUtility.h"
#include "MonsterMannequin.h"
#include "GameFramework/Actor.h"


// Sets default values
AMonsterMannequin::AMonsterMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMonsterMannequin::BeginPlay()
{
	Super::BeginPlay();
	//if(GEngine)
	
}

// Called every frame
void AMonsterMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("Attached"));

}

// Called to bind functionality to input
void AMonsterMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//body of take damage function
bool AMonsterMannequin::TakeDamage(float BaseDamage, float ExtraDamage)
{
	Health -= (BaseDamage + ExtraDamage); //deducting and setting new health value
	if (Health < 0.0) Health = 0.0; // checking bounds
	if (Health) return false; //returning bool
	else return true;
	//UE_LOG(LogTemp, Warning, TEXT("Successful"));
}



// body of setting of monster attack status  
bool AMonsterMannequin::SetAttackStatus(float X, float Y, float Z, float AttackRange)
{

	FVector MonsterPosition = GetActorLocation(); // getting monster real world location


	// returning bool condition
	return (abs(MonsterPosition.X - X) <= AttackRange) & (abs(MonsterPosition.Y - Y) <= AttackRange) & (abs(MonsterPosition.Z - Z) <= 30.0);
}




