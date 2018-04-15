// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PatrollingGaurd.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_BYTES_API APatrollingGaurd : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
		TArray <AActor*> PatrolPointsCPP;
	
	
};
