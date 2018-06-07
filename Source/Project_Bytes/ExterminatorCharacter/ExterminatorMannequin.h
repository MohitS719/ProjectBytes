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
	
	// Default Constructor: Sets default values for this character's properties
	AExterminatorMannequin();			

protected:
	
	// Called when this actor is spawned. Handles initialization events.
	virtual void BeginPlay() override;	

public:

	// UNNECESSARY. Called every frame. 
	virtual void Tick(float DeltaTime) override;															
	// Binds input keys to functionalities
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Handles death event. Repositions gun from Mesh1p to Mesh3p on death. 
	virtual void UnPossessed() override;


private:
	
	// Pawn mesh 1st person view (arms, seen only by self)
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	// First person camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	// Character Movement Component
	class UCharacterMovementComponent *CharacterMovement;		

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
	
	// Handles moving forward/backward
	void MoveForward(float Val);				
	// Handles stafing movement, left and right
	void MoveRight(float Val);					
	// Called via input to turn at a given rate. @param Rate	This is a normalized rate, i.e. 1.0 means 100 % of desired turn rate 
	void TurnAtRate(float Rate);				
	// Called via input to turn look up/down at a given rate. @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate 
	void LookUpAtRate(float Rate);				

public:

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

protected:

	/** Sprint */
	void GoToSprint();			
	/** Walk */
	void GoToWalk();			

public:	
	
	// Is player sprinting?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Details")
	bool bSprinting = false;

private:
	
	/** Different movement speeds */
	float WalkSpeed = 500.0f, SprintSpeed = 1000.f;		


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

	// For Shotgun blueprint attachment
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class AGun> ShotGunBlueprint;

	// For pistol blueprint attachment
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class AGun> PistolBlueprint;

	// For Initiating weapon fire
	UFUNCTION(BlueprintCallable, Category = "Weapon Details")
	void PullTrigger();

	// Is Player Aiming?
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Details")
	bool bAiming = false;

	// Is Player Reloading?
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Details")
	bool bReloading = false;

	// Reload Weapon call
	UFUNCTION(BlueprintCallable, Category = "Character Details")
	void Reload();
	
private:

	// Set bReload State
	void SetReload();

public:

	// Shotgun reference
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	AGun *Shotgun;

	// Pistol Reference
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	AGun *Pistol;

	// Current weapon at hand 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	AGun *CurrentWeapon;

	// Swap weapons 
	UFUNCTION(BlueprintCallable, Category = "Weapon Swapping")
	void ChangeWeapon();

private:

	// Initiate weapon swap
	void ChangeWeaponInitiate();

	// Attach weapon to hand
	void AttachWeaponToGripPoint();

	// Active weapon
	bool IsPistol = false;
	bool IsShotgun = true;

public:

	// Is Player Swapping weapons?
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
