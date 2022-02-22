// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BulletHellJamProjectile.h"
#include "BehaviorTree/BehaviorTree.h"

#include "BulletHellJamPawn.generated.h"

UCLASS(Blueprintable)
class ABulletHellJamPawn : public APawn
{
	GENERATED_BODY()

	/* The mesh component */
	UPROPERTY(Category = Mesh, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ShipMeshComponent;

	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Movement, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		UBehaviorTree* BehaviorTree;

public:
	ABulletHellJamPawn();

	UPROPERTY(Category = Gameplay, EditDefaultsOnly)
		TSubclassOf<ABulletHellJamProjectile> Projectile;
	
	/** Offset from the ships location to spawn projectiles */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite )
		FVector GunOffset = FVector(90.0f,0,0);

	UPROPERTY(Category = Gameplay, VisibleAnywhere, BlueprintReadOnly)
		FRotator FireRotation;
	
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FireRate = 0.1f;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float MaxHealth = 100.0f;

	UPROPERTY(Category = Gameplay, VisibleAnywhere, BlueprintReadOnly)
		float Health = MaxHealth;

	UPROPERTY(Category = Gameplay, VisibleAnywhere, BlueprintReadOnly)
		bool IsDead = false;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		bool IsHit = false;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* FireSound;
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* HitSound;

	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	void FireShot(FVector FireDirection);
	void MoveForward(float velue);
	void MoveRight(float value);
	/* Handler for the fire timer expiry */
	void ShotTimerExpired();
	
	UBehaviorTree* GetBehaviorTree() const;
	
	// Static names for axis bindings
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;

private:
	/* Flag to control firing  */
	uint32 bCanFire : 1;
	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

public:
	/** Returns ShipMeshComponent subobject **/
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
	/** Returns CameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};

