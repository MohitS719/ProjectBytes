// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ExterminatorMannequin.generated.h"

UCLASS()
class PROJECT_BYTES_API AExterminatorMannequin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AExterminatorMannequin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void UnPossessed() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class AGun> GunBlueprint;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PullTrigger();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	int Ammo = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	int MaxAmmo = 100;

	// Pawn mesh 1st person view (arms, seen only by self
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

private:
	// First person camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	AGun *Gun;
};
