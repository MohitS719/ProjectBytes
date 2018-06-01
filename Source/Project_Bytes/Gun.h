// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Gun.generated.h"

UCLASS()
class PROJECT_BYTES_API AGun : public AActor
{
	GENERATED_BODY()

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Sets default values for this actor's properties
	AGun();


	/*
		Weapon Specific properties
	*/

	// Ammo of gun
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Details")
	int Ammo = 100;

	// Max Ammo
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Details")
	int MaxAmmo = 100;

	// Clip Size
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Details")
	int ClipSize = 30;

	// Max Clip Size
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Details")
	int MaxClipSize = 30;

	// Damage Amount
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Details")
	float WeaponDamage = 10.0;

	// Display player ammo full
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Details")
	bool bDisplayAmmoFull = false;

	UPROPERTY()
	class UAnimInstance* AnimInstance1P;

	UPROPERTY()
	class UAnimInstance* AnimInstance3P;

	/*
		Weapon specific functions
	*/

	// Function to Increase Ammo
	UFUNCTION(BlueprintCallable, Category = "Character Details")
	bool IncreaseAmmo(int Amount);

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProject_BytesProjectile> ProjectileClass;

	/** Particle Effect to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UParticleSystem* ParticleEffect;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/** AnimMontages to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation1P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation3P;

	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnFire();

	bool ReloadWeapon();
	
};
