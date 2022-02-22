// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "BlackboardKeys.h"
#include "BulletHellJamPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Macros.h"

AEnemyAIController::AEnemyAIController(FObjectInitializer const& ObjectInitializer){}

void AEnemyAIController::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
	/*UObject* Target = BlackboardComponent()->GetValueAsObject(TargetKey.SelectedKeyName);
	AActor* TargetActor = Cast<AActor>(Target);*/
	
	
	if (auto const BulletHellJamPawn = Cast<ABulletHellJamPawn>(pawn))
	{
		if (UBehaviorTree* const Tree = BulletHellJamPawn->GetBehaviorTree())
		{
			UseBlackboard(Tree->BlackboardAsset, BlackboardComponent);
			RunBehaviorTree(Tree);
		}
	}
	if (BlackboardComponent->GetValueAsObject(blackboardkeys::Target) == nullptr)
	{
		ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		BlackboardComponent->SetValueAsObject(blackboardkeys::Target, player);
	}
}

AActor* AEnemyAIController::GetTargetPawn()
{
	//Return the seeing pawn
	UObject* object = BlackboardComponent->GetValueAsObject(blackboardkeys::Target);

	return object ? Cast<AActor>(object) : nullptr;
}