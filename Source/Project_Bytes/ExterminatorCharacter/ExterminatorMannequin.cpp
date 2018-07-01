// Fill out your copyright notice in the Description page of Project Settings.

#include "ExterminatorMannequin.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														/************************************************************************
														*						FUNDAMENTAL LOGIC START							*
														*				MEMBER FUNCTIONS AND MEMBER VARIABLES					*
														************************************************************************/

// Sets default values
AExterminatorMannequin::AExterminatorMannequin()
{
	// Setting Character Movement
	CharacterMovement = GetCharacterMovement();
	CharacterMovement->MaxWalkSpeed = WalkSpeed;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

}

// Called when the game starts or when spawned
void AExterminatorMannequin::BeginPlay()
{
	Super::BeginPlay();

	// Spawning the shotgun
	if (ShotGunBlueprint == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SHOTGUN BLUEPRINT MISSING!"))
		return;
	}
	else
	{
		Shotgun = GetWorld()->SpawnActor<AGun>(ShotGunBlueprint);
	}

	// Spawning the pistol
	if (PistolBlueprint == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PISTOL BLUEPRINT MISSING!"))
		return;
	}
	else
	{
		Pistol = GetWorld()->SpawnActor<AGun>(PistolBlueprint);
	}

	// Setting Current weapon
	CurrentWeapon = Shotgun;

	// Ataching weapon to hand socket
	AttachWeaponToGripPoint();
	Pistol->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("shotgun_clip"));
	Pistol->SetActorRelativeRotation(RotateWeaponSwapped);

	// Attaching weapon animations
	Shotgun->AnimInstance1P = Mesh1P->GetAnimInstance();
	Shotgun->AnimInstance3P = GetMesh()->GetAnimInstance();

	Pistol->AnimInstance1P = Mesh1P->GetAnimInstance();
	Pistol->AnimInstance3P = GetMesh()->GetAnimInstance();

	// Setting fire input
	if (InputComponent != nullptr)
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &AExterminatorMannequin::PullTrigger);
	}
}

// Called every frame
void AExterminatorMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AExterminatorMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AExterminatorMannequin::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AExterminatorMannequin::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AExterminatorMannequin::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AExterminatorMannequin::LookUpAtRate);

	// Sprinting
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AExterminatorMannequin::GoToSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AExterminatorMannequin::GoToWalk);

	// Reloading
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AExterminatorMannequin::SetReload);

	// Weapon Switching
	PlayerInputComponent->BindAction("SwitchUp", IE_Pressed, this, &AExterminatorMannequin::ChangeWeaponInitiate);
	PlayerInputComponent->BindAction("SwitchDown", IE_Pressed, this, &AExterminatorMannequin::ChangeWeaponInitiate);

	// Invincibility
	PlayerInputComponent->BindAction("Invincibility", IE_Pressed, this, &AExterminatorMannequin::MakeInvincible);

	// Healing
	PlayerInputComponent->BindAction("Heal", IE_Pressed, this, &AExterminatorMannequin::Heal);
}

// On Death event
void AExterminatorMannequin::UnPossessed()
{
	Super::UnPossessed();

	if (Shotgun != NULL)
	{
		Shotgun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
}

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

void AExterminatorMannequin::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AExterminatorMannequin::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AExterminatorMannequin::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AExterminatorMannequin::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

// Goes to sprinting state
void AExterminatorMannequin::GoToSprint()
{
	// Able to sprint. Can't sprint while reloading or aiming down sight
	if (Stamina > 0 && !bReloading && !bAiming && !Swapping)	
	{
		// Is Regeneration going on?
		if (GetWorldTimerManager().IsTimerActive(StaminaRegenerateTimerHandle))
		{
			// Don't Regenrate Stamina anymore
			GetWorldTimerManager().ClearTimer(StaminaRegenerateTimerHandle);
		}

		// Set character to sprint
		CharacterMovement->MaxWalkSpeed = SprintSpeed;

		// Set sprinting state to true
		bSprinting = true;

		// Play sound
		UGameplayStatics::PlaySoundAtLocation(this, SprintingSound, GetActorLocation());

		// Depleting Stamina by 1 per second
		GetWorldTimerManager().SetTimer(StaminaDepleteTimerHandle, this, &AExterminatorMannequin::DepleteStamina, 0.05f, true);
	}
	else				// Not able to sprint. Out of breath
	{
		GoToWalk();		// Slow down
	}

	return;
}

// Goes to walking state
void AExterminatorMannequin::GoToWalk()
{
	// Is Depletion going on?
	if (GetWorldTimerManager().IsTimerActive(StaminaDepleteTimerHandle))
	{
		// Don't Deplete Stamina anymore
		GetWorldTimerManager().ClearTimer(StaminaDepleteTimerHandle);
	}

	// Set character to normal walking speed
	CharacterMovement->MaxWalkSpeed = WalkSpeed;

	bSprinting = false;

	// Is Stamina not Full?
	if (Stamina < MaxStamina)
	{
		// Regenerate Stamina by 1 per second
		GetWorldTimerManager().SetTimer(StaminaRegenerateTimerHandle, this, &AExterminatorMannequin::RegenerateStamina, 0.05f, true);
	}

	return;
}

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

// Damages player. Deducts health by Amount.
bool AExterminatorMannequin::TakeDamage(float Amount)
{
	// Is Player Invincible?
	if (!bInvincibility)
	{
		// Is Player Alive?
		if (!bIsDead)	
		{
			// Deduct health. As in plaer is taking damage
			Health -= Amount;

			// Turning on display Damage Indicator
			bTakingDamage = true;	

			// Play sound
			UGameplayStatics::PlaySoundAtLocation(this, GruntingSound, GetActorLocation());

			// Boundary Check
			if (Health <= 0.0)		
			{
				// Health can't be negative
				Health = 0.0;

				// Killed player
				bIsDead = true;		
			}
			else if (Health <= 20)
			{
				// Play sound
				UGameplayStatics::PlaySoundAtLocation(this, SoundLowHealth, GetActorLocation());

				// Display low health
				Indicator = 11;

				// Display indicator for sometime
				GetWorldTimerManager().SetTimer(IndicatorTimerHandle, this, &AExterminatorMannequin::TurnOffIndicator, 2.0f, true);
			}
		}
	}

	// Return death status. True for dead. False for alive.
	return bIsDead;
}

// Regenerate player's stamina when walking.
void AExterminatorMannequin::RegenerateStamina()
{
	// Boundary check.
	if (Stamina < MaxStamina)
	{
		// Regenerate stamina
		Stamina += 0.05f;
	}
	// Stamina full. Turn off regeneration.
	else if (GetWorldTimerManager().IsTimerActive(StaminaRegenerateTimerHandle))
	{
		// Don't regenerate Stamina anymore
		GetWorldTimerManager().ClearTimer(StaminaRegenerateTimerHandle);
	}

	/*UE_LOG(LogTemp, Warning, TEXT("Walking"));*/

	return;
}

// Depletes player's stamina when sprinting.
void AExterminatorMannequin::DepleteStamina()
{
	// Boundary check
	if (Stamina > 0.0)
	{
		// Deplete stamina
		Stamina -= 0.05f;
	}
	// Player is exhausted.
	else
	{
		// Can't sprint. Just walk.
		GoToWalk();
	}

	/*UE_LOG(LogTemp, Warning, TEXT("Sprinting"));*/

	return;
}

// Increase player's token by IncreaseAmount
void AExterminatorMannequin::IncreaseTokens(int IncreaseAmount)
{
	Tokens += IncreaseAmount;

	return;
}

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

// Initiates means that just calling the function that actually does it or just turning a boolean value to true. 

// Initiates gun firing. Actual firing logic at Gun.cpp
void AExterminatorMannequin::PullTrigger()
{
	// Check If Gun Has Enough Ammo in the clip to fire.If player is reloading or sprinting or swapping, then he can't shoot.
	if (CurrentWeapon->ClipSize > 0 && !bReloading && !bSprinting && !Swapping)	
	{
		// Decrease one hit kill amount if there is any
		if (OneHitKillAmmo)
		{
			OneHitKillAmmo--;
		}

		// Yes. Tell Gun To Fire
		CurrentWeapon->OnFire();	
	}
	else if (CurrentWeapon->ClipSize <= 0)
	{
		// Call Reload
		SetReload();
	}

	return;
}

// Calls actual reload function. This gets called by the Animation blueprint.
void AExterminatorMannequin::Reload()
{

	// Call weapon reload function
	bReloading = !(CurrentWeapon->ReloadWeapon());

	return;
}

// Initiates reloading. Actual relading logic at Gun.cpp
void AExterminatorMannequin::SetReload()
{
	// If not sprinting, aiming or swapping weapons then he can reload
	if (!bSprinting && !bAiming && !Swapping)
	{
		// Checking if there is ammo to reload and if the clip is empty
		if ((CurrentWeapon->Ammo > 0) && (CurrentWeapon->ClipSize < CurrentWeapon->MaxClipSize))
		{
			// Set reload state to true
			bReloading = true;

			// Play sound
			UGameplayStatics::PlaySoundAtLocation(this, WeaponReloading, GetActorLocation());
		}
		else if (CurrentWeapon->Ammo == 0)
		{
			// No ammo to reload
			TurnOnIndicator(10, 2.0f);
		}
	}

	return;
}

// Initiates swapping or changing weapons. Actual changing logic is ChangeWeapon() function.
void AExterminatorMannequin::ChangeWeaponInitiate()
{
	// If player isn't sprinting, aiming and reloading then he can change weapons
	if (!bSprinting && !bAiming && !bReloading)
	{
		// Set player state to swapping weapons.
		Swapping = true;

		// Is Shotgun the current weapon?
		if (IsShotgun)
		{
			// Then swap the shotgun for the pistol
			IsShotgun = false;
			IsPistol = true;
		}
		else
		{
			// Otherwise swap the pistol for the shotgun
			IsShotgun = true;
			IsPistol = false;
		}
	}

	return;
}

// Changes weapons. Called by the Animation Blueprint.
void AExterminatorMannequin::ChangeWeapon()
{
	// Detach from hand.
	CurrentWeapon->DetachRootComponentFromParent();
	
	// Attach weapon to the back.
	CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("shotgun_clip"));
	
	// Correctly position the weapon on the back so it doesn't stick out.
	CurrentWeapon->SetActorRelativeRotation(RotateWeaponSwapped);

	// Play sound
	UGameplayStatics::PlaySoundAtLocation(this, WeaponSwitching, GetActorLocation());

	// Is Pistol suppose to be the current weapon?
	if (IsPistol)
	{
		CurrentWeapon = Pistol;

		/*UE_LOG(LogTemp, Warning, TEXT("PISTOL"))*/
	}
	// Shotgun is supposed to be the current weapon.
	else
	{
		CurrentWeapon = Shotgun;

		/*UE_LOG(LogTemp, Warning, TEXT("SHOTGUN"))*/
	}

	// Attach current weapon to hand.
	AttachWeaponToGripPoint();

	return;
}

// Attach the current weapon to grippoint which is the hand.
void AExterminatorMannequin::AttachWeaponToGripPoint()
{
	// Is the character player controlled? Then attach it to mesh1p. Otherwise attach to mesh3p.
	if (IsPlayerControlled())
	{
		// Ataching weapon to GripPoint socket
		CurrentWeapon->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
	else
	{
		// Ataching weapon to GripPoint socket
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}

	if (IsPistol)
	{
		CurrentWeapon->SetActorRelativeRotation(RotatePistol);
		CurrentWeapon->SetActorRelativeLocation(LocatePistol);
	}

	return;
}


														/************************************************************************
														*					WEAPON RELATED LOGIC END							*
														*				MEMBER FUNCTIONS AND MEMBER VARIABLES					*
														************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														/************************************************************************
														*						PICKUP RELATED LOGIC START						*
														*				MEMBER FUNCTIONS AND MEMBER VARIABLES					*
														************************************************************************/

// Player tries to pickup invincibility pickup
bool AExterminatorMannequin::PickUpInvincibility()
{
	// Can player pickup
	if (InvincibilityPickups < MaxInvincibilityPickups)
	{
		// Yes.
		++InvincibilityPickups;

		// Play success sound
		UGameplayStatics::PlaySoundAtLocation(this, SoundPickupSuccess, GetActorLocation());

		return true;
	}
	else
	{
		// Play failure sound
		UGameplayStatics::PlaySoundAtLocation(this, SoundPickupFailed, GetActorLocation());

		// Set indicator
		TurnOnIndicator(3, 2.0f);
		
		return false;
	}
	
}

// Makes player invincible. Meaning he can't take damage.
void AExterminatorMannequin::MakeInvincible()
{
	// If player isn't already invincible then he can become invincible
	if (!bInvincibility)
	{
		// If player has invincibility pickups then he can become invincibile
		if (InvincibilityPickups)
		{
			// Become invincible
			bInvincibility = true;

			// Decrease Invincibility pickup
			InvincibilityPickups--;

			// Set time limit to invincibility
			GetWorldTimerManager().SetTimer(InvincibleTimerHandle, this, &AExterminatorMannequin::MakeMortal, InvincibleTimer, true);
		}
		else
		{
			// No invincibility pickups
			TurnOnIndicator(9, 2.0f);

			// Failed sound
			UGameplayStatics::PlaySoundAtLocation(this, SoundPickupFailed, GetActorLocation());
		}
	}
	else
	{
		// Already invincible
		TurnOnIndicator(5, 2.0f);

		// Failed sound
		UGameplayStatics::PlaySoundAtLocation(this, SoundPickupFailed, GetActorLocation());
	}
	
	return;
}

// Makes player a mortal. Meaning he can take damage.
void AExterminatorMannequin::MakeMortal()
{
	// If invincibility is on, then turn it on
	if (bInvincibility)
	{
		// Turn off invincibility
		bInvincibility = false;

		// Checking if timer is on
		if (GetWorldTimerManager().IsTimerActive(InvincibleTimerHandle))
		{
			// Clear timer 
			GetWorldTimerManager().ClearTimer(InvincibleTimerHandle);
		}
	}
	
	return;
}

// Increases One hit kill ammo
bool AExterminatorMannequin::PickupOneHitKill()
{
	if (OneHitKillAmmo < MaxOneHitKillAmmo)
	{
		// Increase on hit kill ammo
		OneHitKillAmmo += 5;

		// Boundary checking
		if (OneHitKillAmmo > MaxOneHitKillAmmo)
		{
			OneHitKillAmmo = MaxOneHitKillAmmo;
		}

		// Play success sound
		UGameplayStatics::PlaySoundAtLocation(this, SoundPickupSuccess, GetActorLocation());

		return true;
	}
	else
	{
		// Play failure sound
		UGameplayStatics::PlaySoundAtLocation(this, SoundPickupFailed, GetActorLocation());

		// One hit kill full
		TurnOnIndicator(7, 2.0f);
	}

	return false;
}

// Heals player. Regenerates health by Amount.
void AExterminatorMannequin::Heal()
{
	// Does player have item to heal?
	if (HealthPickups)
	{
		// Is it possible to Heal?
		if (Health < MaxHealth)
		{
			// Use Health pickup
			--HealthPickups;

			// Heal
			Health += HealAmount;

			// Boundary Check
			if (Health > MaxHealth)
			{
				Health = MaxHealth;
			}

			// Healing sound
			UGameplayStatics::PlaySoundAtLocation(this, SoundHeal, GetActorLocation());
		}
		else
		{
			// Health full. Turn on display health full indicator
			TurnOnIndicator(1, 2.0f);

			// Failed sound
			UGameplayStatics::PlaySoundAtLocation(this, SoundPickupFailed, GetActorLocation());
		}
	}
	else
	{
		// Empty health pickup
		TurnOnIndicator(8, 2.0);

		// Failed sound
		UGameplayStatics::PlaySoundAtLocation(this, SoundPickupFailed, GetActorLocation());
	}

	return;
}

// Pick up a key card
bool AExterminatorMannequin::PickupKeycard()
{
	if (KeyCards < MaxKeyCards)
	{
		// Play success sound
		UGameplayStatics::PlaySoundAtLocation(this, SoundPickupSuccess, GetActorLocation());

		// Increase key cards
		++KeyCards;

		return true;
	}
	else
	{
		// Key card full
		TurnOnIndicator(6, 2.0f);

		// Play failure sound
		UGameplayStatics::PlaySoundAtLocation(this, SoundPickupFailed, GetActorLocation());

		return false;
	}

}

bool AExterminatorMannequin::UseKeycard()
{
	if (KeyCards > 0)
	{
		// Use key card
		--KeyCards;

		return true;
	}
	else
	{
		// Display indicator no keycard
		TurnOnIndicator(12, 2.0f);

		return false;
	}
}

// Pick up a health pickup or health restoration item
bool AExterminatorMannequin::PickupHealth()
{
	// Can the player pick up?
	if (HealthPickups < MaxHealthPickups)
	{
		// Increase Health pickups
		++HealthPickups;

		// Play success sound
		UGameplayStatics::PlaySoundAtLocation(this, SoundPickupSuccess, GetActorLocation());

		return true;
	}
	else
	{
		// Play failure sound
		UGameplayStatics::PlaySoundAtLocation(this, SoundPickupFailed, GetActorLocation());

		// Health pickups full
		TurnOnIndicator(4, 2.0f);
	}

	return false;
}

void AExterminatorMannequin::TurnOnIndicator(int Value, float Span)
{
	// Health pickups full
	Indicator = Value;

	// Display indicator for sometime
	GetWorldTimerManager().SetTimer(IndicatorTimerHandle, this, &AExterminatorMannequin::TurnOffIndicator, Span, true);

	return;
}

// Turns of indicator
void AExterminatorMannequin::TurnOffIndicator()
{
	// Checking if timer is on
	if (GetWorldTimerManager().IsTimerActive(IndicatorTimerHandle))
	{
		// Resetting indicator
		Indicator = 0;

		// Clear timer 
		GetWorldTimerManager().ClearTimer(IndicatorTimerHandle);
	}

	return;
}

													/************************************************************************
													*						PICKUP RELATED LOGIC END						*
													*				MEMBER FUNCTIONS AND MEMBER VARIABLES					*
													************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
