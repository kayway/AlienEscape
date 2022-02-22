// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletHellJamProjectile.generated.h"


class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS(config=Game)
class ABulletHellJamProjectile : public AActor
{
	GENERATED_BODY()

	//bool IsBomb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ProjectileMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;
public:
	ABulletHellJamProjectile();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Projectile)
		float Damage;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Projectile)
		bool DestroyThis;
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);
	/** Returns ProjectileMesh subobject **/
	FORCEINLINE UStaticMeshComponent* GetProjectileMeshComponent() const { return ProjectileMeshComponent; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

