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

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/** Sprint */
	void GoToSprint();

	/** Walk */
	void GoToWalk();

	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

public:

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void UnPossessed() override;

	/*
		Weapon Sppecific Variables and Functions
		Contains Ammo, MaxAmmo, Clipsize, MaxClipSize, Damage
	*/

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class AGun> GunBlueprint;

	UFUNCTION(BlueprintCallable, Category = "Weapon Details")
	void PullTrigger();

	// Ammo of gun
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Details")
	int Ammo = 100;

	// Max Ammo
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Details")
	int MaxAmmo = 100;

	// Clip Size
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Details")
	int ClipSize = 100;

	// Max Clip Size
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Details")
	int MaxClipSize = 100;

	// Damage Amount
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Details")
	float WeaponDamage = 10.0;

	// Display player ammo full
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Details")
	bool bDisplayAmmoFull = false;

	/*
		Character Detail Specific Variables And Functions
		Contains Health, MaxHealth, Stamina, MaxStamina
	*/

	// Player Health
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Details")
	float Health = 100.0;

	// Player Max Health
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Details")
	float MaxHealth = 100.0;

	// Heal Player, returns successful healing or not
	UFUNCTION(BlueprintCallable, Category = "Character Details")
	bool Heal(float Amount);

	// Damage player, return true if damaged
	UFUNCTION(BlueprintCallable, Category = "Character Details")
	bool TakeDamage(float Amount);

	// Display player health full
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Details")
	bool bDisplayHealthFull = false;

	// Display player taking damage
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Details")
	bool bTakingDamage = false;

	// Player Dead?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Details")
	bool bIsDead = false;
	
	// Player Death Called?
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Details")
	bool bDeathEventCalled = false;

	// Player Stamina
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Details")
	int Stamina = 10;

	// Player Max Stamina
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Details")
	int MaxStamina = 10;

private:
	// Regenerate stamina
	UFUNCTION()
	void RegenerateStamina();

	// Deplete Stamina
	UFUNCTION()
	void DepleteStamina();

	// Timer Handle for Stamina regeneration
	FTimerHandle StaminaRegenerateTimerHandle;

	// Timer Handle for Stamina depletion
	FTimerHandle StaminaDepleteTimerHandle;

public:
	// Player Tokens
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Details")
	int Tokens = 10;

	// Increase Player Token
	UFUNCTION(BlueprintCallable, Category = "Character Details")
	void IncreaseTokens(int IncreaseAmount);

	// Purchase using Player Token
	UFUNCTION(BlueprintCallable, Category = "Character Details")
	bool Purchase(int UpgradePrice, int UpgradeType);


private:
	// Pawn mesh 1st person view (arms, seen only by self
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	// First person camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	// Attaching Gun BP
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	AGun *Gun; 

	// Character Movement Component
	class UCharacterMovementComponent *CharacterMovement;

	// Walk speed
	float WalkSpeed = 500.0f, SprintSpeed = 1000.f;
};
