// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Project_BytesProjectile.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;

	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	// Setup muzzle location
	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = FP_MuzzleLocation->GetComponentRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = FP_MuzzleLocation->GetComponentLocation();

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<AProject_BytesProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

			// Spawn Particle
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleEffect, FP_MuzzleLocation->GetComponentLocation(), FP_MuzzleLocation->GetComponentRotation());
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation1P != nullptr && AnimInstance1P != nullptr)
	{	
		AnimInstance1P->Montage_Play(FireAnimation1P, 1.f);	
	}
	if (FireAnimation3P != nullptr && AnimInstance3P != nullptr)
	{
		AnimInstance3P->Montage_Play(FireAnimation3P, 1.f);
	}

	// Decrease Ammo
	--ClipSize;
}

bool AGun::ReloadWeapon()
{
	// Is reload necessary?
	if (ClipSize != MaxClipSize)
	{
		// Deducting from total ammo
		Ammo -= (MaxClipSize-ClipSize);

		// Refilling clip
		ClipSize = MaxClipSize;

		// Boundary Checking
		if (Ammo <= 0)
		{
			ClipSize += Ammo;
			Ammo = 0;
		}

		// Reload Successful
		return true;
	}

	// Reload Failed
	return false;
}

bool AGun::IncreaseAmmo(int Amount)
{
	if (Ammo < MaxAmmo)		// Checking whether ammo can be taken
	{
		Ammo += Amount;		// Ammo Taken

		if (Ammo > MaxAmmo)	// Boundary check
		{	
			Ammo = MaxAmmo;
		}

		bDisplayAmmoFull = false;	// No need to display full ammo

		return true;		// Pickup successfull
	}
	else
	{
		bDisplayAmmoFull = true;	// Show player ammo full
	}

	return false;			// Pick up failed
}
