// Copyright Epic Games, Inc. All Rights Reserve

#include "BulletHellJamProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Macros.h"
#include "Kismet/GameplayStatics.h"

ABulletHellJamProjectile::ABulletHellJamProjectile() 
{

	// Create mesh component for the projectile sphere
	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMeshComponent->SetNotifyRigidBodyCollision(true);
	ProjectileMeshComponent->SetCollisionProfileName("Projectile");
	RootComponent = ProjectileMeshComponent;
	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = ProjectileMeshComponent;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->bConstrainToPlane = true;
	ProjectileMovement->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);
	Tags.Add(FName("Bullet"));
	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
	Damage = 10.0f;
	/*Radius = 10.0f;
	IsBomb = Type == ProjectileType::Bomb;*/
}

void ABulletHellJamProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMeshComponent->OnComponentHit.AddDynamic(this, &ABulletHellJamProjectile::OnHit);
	ProjectileMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ABulletHellJamProjectile::OnBeginOverlap);
}

void ABulletHellJamProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
			DestroyThis = true;
		}
		else if ((OtherActor->ActorHasTag(FName("RedProjectile")) && ActorHasTag(FName("RedProjectile"))) ||
			(OtherActor->ActorHasTag(FName("BlueProjectile")) && ActorHasTag(FName("BlueProjectile"))) ||
			(OtherActor->ActorHasTag(FName("GreenProjectile")) && ActorHasTag(FName("GreenProjectile"))))
		{
			DestroyThis = true;
		}
	}
}
void ABulletHellJamProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && DestroyThis == false)
	{
		if (ActorHasTag(FName("BlueProjectile")) && OtherActor->ActorHasTag(FName("Player")) || (ActorHasTag(FName("RedProjectile")) && OtherActor->ActorHasTag(FName("Enemy"))))
		{
		}
		else
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, this->GetInstigatorController(), GetOwner(), UDamageType::StaticClass());
			DestroyThis = true;
		}
	}
}