// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetLOSDecorator.h"
#include "EnemyAIController.h"
#include "BulletHellJamPawn.h"
#include "Macros.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UTargetLOSDecorator::UTargetLOSDecorator(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("TargetInLOS");
}
bool UTargetLOSDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool HasLOS = true;
	if (AAIController* const Cont = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()))
	{
		if (ABulletHellJamPawn* const BulletHellJamPawn = Cast<ABulletHellJamPawn>(Cont->GetPawn()))
		{	
			UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey.SelectedKeyName);
			// Perform trace to retrieve hit info
			AActor* TargetActor = Cast<AActor>(Target);
			FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(AILosTrace), true, OwnerComp.GetOwner());
			TraceParams.bReturnPhysicalMaterial = true;
			TArray<AActor*> FoundActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABulletHellJamProjectile::StaticClass(), FoundActors);
			const FVector StartLocation = BulletHellJamPawn->GetActorLocation()/* + (BulletHellJamPawn->GetActorForwardVector() * 100)*/;
			if (TargetActor)
			{
				const FVector EndLocation = TargetActor->GetActorLocation();
				FHitResult Hit(ForceInit);
				GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility, TraceParams);
				
				if (Hit.bBlockingHit == true)
				{
					//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true);
					HasLOS = false;
					// We hit something. If we have an actor supplied, just check if the hit actor is an enemy. If it is consider that 'has LOS'
					AActor* HitActor = Hit.GetActor();
					if (Hit.GetActor() != NULL)
					{
						// If the hit is our target actor consider it LOS
						if (HitActor->ActorHasTag(FName("Player")))
						{
							HasLOS = true;
						}
					}
				}
			}
		}
	}
	return HasLOS;
}