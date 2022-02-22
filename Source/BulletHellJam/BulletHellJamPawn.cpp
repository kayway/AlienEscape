// Copyright Epic Games, Inc. All Rights Reserved.

#include "BulletHellJamPawn.h"
#include "BulletHellJamProjectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Macros.h"

const FName ABulletHellJamPawn::MoveForwardBinding("MoveForward");
const FName ABulletHellJamPawn::MoveRightBinding("MoveRight");
const FName ABulletHellJamPawn::FireForwardBinding("FireForward");
const FName ABulletHellJamPawn::FireRightBinding("FireRight");

ABulletHellJamPawn::ABulletHellJamPawn()
{	
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	//RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	
	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 2000.f;
	CameraBoom->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;
	MovementComponent->bConstrainToPlane = true;
	MovementComponent->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);

	bCanFire = true;
}
void ABulletHellJamPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding, this, &ABulletHellJamPawn::MoveForward);
	PlayerInputComponent->BindAxis(MoveRightBinding, this, &ABulletHellJamPawn::MoveRight);
	PlayerInputComponent->BindAxis(FireForwardBinding);
	PlayerInputComponent->BindAxis(FireRightBinding);
}

void ABulletHellJamPawn::MoveForward(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
		SetActorRotation(GetLastMovementInputVector().Rotation());
	}
}
void ABulletHellJamPawn::MoveRight(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, value);
		SetActorRotation(GetLastMovementInputVector().Rotation());
	}
}
void ABulletHellJamPawn::Tick(float DeltaSeconds)
{
	MovementComponent->SnapUpdatedComponentToPlane();
	// Create fire direction vector
	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const float FireRightValue = GetInputAxisValue(FireRightBinding);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);
	// Try and fire a shot
	FireShot(FireDirection);
}
void ABulletHellJamPawn::FireShot(FVector FireDirection)
{
	// If it's ok to fire again
	if (bCanFire == true)
	{
		// If we are pressing fire stick in a direction
		if (FireDirection.SizeSquared() > 0.0f)
		{
			FireRotation = FireDirection.Rotation();
			// Spawn projectile at an offset from this pawn
			const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				FActorSpawnParameters Params;
				Params.Owner = this;
				// spawn the projectile
				World->SpawnActor<ABulletHellJamProjectile>(Projectile, SpawnLocation, FireRotation, Params);
			}

			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ABulletHellJamPawn::ShotTimerExpired, FireRate);

			// try and play the sound if specified
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			bCanFire = false;
		}
	}
}
void ABulletHellJamPawn::ShotTimerExpired()
{
	bCanFire = true;
}
float ABulletHellJamPawn::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	if (DamageAmount == 0.0)
		return 0.0f;
	else
	{
		if (DamageAmount > 0.0 && HitSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}
		Health = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth);
	}
	if (Health == 0.0f)
		IsDead = true;
	return Health;
}
UBehaviorTree* ABulletHellJamPawn::GetBehaviorTree() const
{
	return BehaviorTree;
}