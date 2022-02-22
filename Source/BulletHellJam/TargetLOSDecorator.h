// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "TargetLOSDecorator.generated.h"

/**
 * 
 */
UCLASS()
class BULLETHELLJAM_API UTargetLOSDecorator : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	
	UTargetLOSDecorator(FObjectInitializer const& ObjectInitializer);

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
private:
	UPROPERTY(EditAnywhere, Category = Blackboard, meta = (AllowPrivateAccess = "true"))
		struct FBlackboardKeySelector TargetKey;
};
