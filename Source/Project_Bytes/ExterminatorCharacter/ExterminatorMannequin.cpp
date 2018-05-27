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

// Sets default values
AExterminatorMannequin::AExterminatorMannequin()
{
	CharacterMovement = GetCharacterMovement();
	WalkSpeed = CharacterMovement->MaxWalkSpeed;

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
	CharacterMovement->MaxWalkSpeed = WalkSpeed * 2.0;
}

void AExterminatorMannequin::GoToWalk()
{
	CharacterMovement->MaxWalkSpeed = WalkSpeed / 2.0;
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

void AExterminatorMannequin::IncreaseTokens(int IncreaseAmount)
{
	Tokens += IncreaseAmount;

	return;
}

bool AExterminatorMannequin::Purchase(int UpgradePrice, int UpgradeType)
{
	bool PurchaseSuccess = false;

	if (Tokens >= UpgradePrice)		// Able to afford upgrade
	{
		switch (UpgradeType)		// Selecting the upgrade for puchase
		{
		// Max Ammo Capacity Increase
		case 1:	
			MaxAmmo += 10;			// Increase Max Ammo Capacity
			PurchaseSuccess = true;
			break;

		// Damage Increase
		case 2:
			WeaponDamage += 5.0;			// Increase Damage of Weapon
			PurchaseSuccess = true;
			break;

		// Max Health Capacity Increase
		case 3:
			MaxHealth += 10;		// Increase Max Health
			PurchaseSuccess = true;
			break;

		// Replenish Health
		case 4:
			if (Health < MaxHealth)	// Replenish possible
			{
				Health = MaxHealth;	// Heal
				PurchaseSuccess = true;
			}
			break;

		// Replenish Ammo
		case 5:	
			if (Ammo < MaxAmmo)	// Replenish possible
			{
				Ammo = MaxAmmo;	// Replenish Ammo
				PurchaseSuccess = true;
			}
			break;
		}
		
		// Check if Purchase successful
		if (PurchaseSuccess)
		{
			Tokens -= UpgradePrice;	// Deduct upgrade price
		}
	}

	return PurchaseSuccess;			// Purchase unsuccessful
}
