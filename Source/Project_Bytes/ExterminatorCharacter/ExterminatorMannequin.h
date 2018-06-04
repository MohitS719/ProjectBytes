// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ExterminatorMannequin.generated.h"


UCLASS()
class PROJECT_BYTES_API AExterminatorMannequin : public ACharacter
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
													/************************************************************************
													*						FUNDAMENTAL LOGIC START							*
													*				MEMBER FUNCTIONS AND MEMBER VARIABLES					*
													************************************************************************/
	GENERATED_BODY()

public:
	
	AExterminatorMannequin();			// Sets default values for this character's properties

protected:
	
	virtual void BeginPlay() override;	// Called when the game starts or when spawned

public:

	virtual void Tick(float DeltaTime) override;															// Called every frame
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;			// Called to bind functionality to input
	virtual void UnPossessed() override;


private:
	
	// Pawn mesh 1st person view (arms, seen only by self
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	// First person camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	class UCharacterMovementComponent *CharacterMovement;		// Character Movement Component

													/************************************************************************
													*						FUNDAMENTAL LOGIC END							*
													*				MEMBER FUNCTIONS AND MEMBER VARIABLES					*
													************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
													/************************************************************************
													*					MOVEMENT RELATED LOGIC START						*
													*				MEMBER FUNCTIONS AND MEMBER VARIABLES					*
													************************************************************************/

protected:
	
	void MoveForward(float Val);				/** Handles moving forward/backward */
	void MoveRight(float Val);					/** Handles stafing movement, left and right */
	void TurnAtRate(float Rate);				/** Called via input to turn at a given rate. @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate */
	void LookUpAtRate(float Rate);				/** Called via input to turn look up/down at a given rate. @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate */

public:

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

protected:

	void GoToSprint();			/** Sprint */
	void GoToWalk();			/** Walk */

public:	
	
	// Is player sprinting?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Details")
	bool bSprinting = false;

private:
	
	float WalkSpeed = 500.0f, SprintSpeed = 1000.f;		/** Different movement speeds */


													/************************************************************************
													*					MOVEMENT RELATED LOGIC END							*
													*				MEMBER FUNCTIONS AND MEMBER VARIABLES					*
													************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
													/************************************************************************
													*					PROPERTY RELATED LOGIC START						*
													*				MEMBER FUNCTIONS AND MEMBER VARIABLES					*
													************************************************************************/
public:

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

													/************************************************************************
													*					PROPERTY RELATED LOGIC END							*
													*				MEMBER FUNCTIONS AND MEMBER VARIABLES					*
													************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
													/************************************************************************
													*					WEAPON RELATED LOGIC START							*
													*				MEMBER FUNCTIONS AND MEMBER VARIABLES					*
													************************************************************************/

public:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class AGun> ShotGunBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class AGun> PistolBlueprint;

	UFUNCTION(BlueprintCallable, Category = "Weapon Details")
	void PullTrigger();


	// Player Aiming
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Details")
	bool bAiming = false;

	// Player Reloading
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Details")
	bool bReloading = false;

	// Reload Weapon call
	UFUNCTION(BlueprintCallable, Category = "Character Details")
	void Reload();

	// Set bReload State
	void SetReload();

	// Attaching Shotgun BP
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	AGun *Shotgun;

	// Attaching pistol BP
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	AGun *Pistol;

	// Attaching pistol BP
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	AGun *CurrentWeapon;


	UFUNCTION(BlueprintCallable, Category = "Weapon Swapping")
	void ChangeWeapon();

	void ChangeWeaponInitiate();
	void AttachWeaponToGripPoint();

	// Active weapon
	bool IsPistol = false;
	bool IsShotgun = true;

	// Bool for swapping
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Rotation Details")
	bool Swapping = false;

	// Rotating weapon swapped
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Rotation Details")
	FRotator RotateWeaponSwapped = FRotator(0, 0, 90);

													/************************************************************************
													*					WEAPON RELATED LOGIC END							*
													*				MEMBER FUNCTIONS AND MEMBER VARIABLES					*
													************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

};
