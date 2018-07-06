// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UnrealMathUtility.h"
#include "GameFramework/Actor.h"
#include "MonsterMannequin.generated.h"

UCLASS()
class PROJECT_BYTES_API AMonsterMannequin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterMannequin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame Not Needed anymore
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	// Health is now in cpp declaring variable
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Props")
	float Health = 0.0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Props")
	bool isdead = false;


	// monster characteristics taking damage and setting new values
	UFUNCTION(BlueprintCallable, Category = "Character Props")
	bool TakeDamage(float BaseDamage, float extraDamage);

	// setting attack status and moved to monster blueprint previously in monster AI
	UFUNCTION(BlueprintCallable, Category = "Character Props")
	bool SetAttackStatus(float X, float Y, float Z,float AttackRange);

	

	
};
