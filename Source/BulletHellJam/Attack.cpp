// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack.h"
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "BlackboardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"

UAttack::UAttack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get AI controller and its NPC
	if (AAIController* const Cont = OwnerComp.GetAIOwner())
	{
		if (ABulletHellJamPawn* const BulletHellJamPawn = Cast<ABulletHellJamPawn>(Cont->GetPawn()))
		{
			FVector Direction = FVector(0.0, 0.0, 1.0);
			FVector OriginLocation = BulletHellJamPawn->GetActorLocation();
			UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey.SelectedKeyName);
			AActor* TargetActor = Cast<AActor>(Target);
			FVector TargetLocation;
			if (TargetActor)
				TargetLocation = TargetActor->GetActorLocation();
			FRotator TargetDirection = UKismetMathLibrary::FindLookAtRotation(OriginLocation, TargetLocation);
			//BulletHellJamPawn->SetActorRotation(TargetDirection);
			BulletHellJamPawn->FireShot(TargetDirection.Vector());
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}