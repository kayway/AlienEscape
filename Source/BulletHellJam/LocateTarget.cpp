// Fill out your copyright notice in the Description page of Project Settings.


#include "LocateTarget.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BlackboardKeys.h"
#include "BaseLevel.h"
#include "Macros.h"

ULocateTarget::ULocateTarget(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Locate Target");
}

EBTNodeResult::Type ULocateTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get AI controller and its NPC
	if (AAIController* const Cont = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()))
	{
		FVector NewLocation;
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ABulletHellJamPawn::StaticClass(), FName("Player"), FoundActors);
		//QuickPrint(FString::Printf(TEXT("New Location: %s"), *NewLocation.ToString()));
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocationVectorKey.SelectedKeyName, FoundActors[0]->GetActorLocation());
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
