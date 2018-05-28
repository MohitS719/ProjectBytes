// Fill out your copyright notice in the Description page of Project Settings.

#include "ExterminatorMannequin.h"
#include "Project_Bytes.h"
#include "../Gun.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Public/TimerManager.h"

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
	if (GunBlueprint == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GIN BLUEPRINT MISSING!"))
		return;
	}

	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	if (IsPlayerControlled())
	{
		Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
	else
	{
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}

	Gun->AnimInstance1P = Mesh1P->GetAnimInstance();
	Gun->AnimInstance3P = GetMesh()->GetAnimInstance();

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
}

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

void AExterminatorMannequin::GoToSprint()
{
	if (Stamina > 0)	// Able to sprint
	{
		// Is Regeneration going on?
		if (GetWorldTimerManager().IsTimerActive(StaminaRegenerateTimerHandle))
		{
			// Don't Regenrate Stamina anymore
			GetWorldTimerManager().ClearTimer(StaminaRegenerateTimerHandle);
		}

		// Set character to sprint
		CharacterMovement->MaxWalkSpeed = SprintSpeed;

		// Depleting Stamina by 1 per second
		GetWorldTimerManager().SetTimer(StaminaDepleteTimerHandle, this, &AExterminatorMannequin::DepleteStamina, 1.0f, true);
	}
	else				// Not able to sprint. Out of breath
	{
		GoToWalk();		// Slow down
	}

	return;
}

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

	// Is Stamina not Full?
	if (Stamina < MaxStamina)
	{
		// Regenerate Stamina by 1 per second
		GetWorldTimerManager().SetTimer(StaminaRegenerateTimerHandle, this, &AExterminatorMannequin::RegenerateStamina, 1.0f, true);
	}

	return;
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

void AExterminatorMannequin::UnPossessed()
{
	Super::UnPossessed();

	if (Gun != NULL)
	{
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
}

void AExterminatorMannequin::PullTrigger()
{
	if (Ammo > 0)
	{
		Gun->OnFire();
		Ammo--;
	}

	return;
}

bool AExterminatorMannequin::Heal(float Amount)
{
	if (Health < MaxHealth)		// Possible to Heal
	{
		Health += Amount;		// Heal

		if (Health > MaxHealth)	// Boundary Check
		{
			Health = MaxHealth;
		}

		bDisplayHealthFull = false;

		return true;			// Successful healing
	}
	else
	{
		bDisplayHealthFull = true;
	}

	return false;				// Unsuccessful healing
}

bool AExterminatorMannequin::TakeDamage(float Amount)
{
	if (!bIsDead)	// Is Player Alive?
	{
		Health -= Amount;

		bTakingDamage = true;	// Turning on Damage Indicator

		if (Health <= 0.0)		// Boundary Check
		{
			Health = 0.0;

			bIsDead = true;		// Killed player
		}
	}

	return bIsDead;
}

void AExterminatorMannequin::RegenerateStamina()
{
	if (Stamina < MaxStamina)
	{
		++Stamina;
	}
	else if (GetWorldTimerManager().IsTimerActive(StaminaRegenerateTimerHandle))
	{
		// Don't Deplete Stamina anymore
		GetWorldTimerManager().ClearTimer(StaminaRegenerateTimerHandle);
	}

	UE_LOG(LogTemp, Warning, TEXT("Walking"));

	return;
}

void AExterminatorMannequin::DepleteStamina()
{
	if (Stamina > 0)
	{
		--Stamina;
	}
	else
	{
		GoToWalk();
	}

	UE_LOG(LogTemp, Warning, TEXT("Sprinting"));

	return;
}

void AExterminatorMannequin::IncreaseTokens(int IncreaseAmount)
{
	Tokens += IncreaseAmount;

	return;
}
