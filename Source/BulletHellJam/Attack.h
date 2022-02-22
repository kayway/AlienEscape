// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BulletHellJamPawn.h"

#include "Attack.generated.h"

/**
 * 
 */
UCLASS()
class BULLETHELLJAM_API UAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UAttack(FObjectInitializer const& ObjectInitializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	UPROPERTY(EditAnywhere, Category = Blackboard, meta = (AllowPrivateAccess = "true"))
		struct FBlackboardKeySelector TargetKey;
};
