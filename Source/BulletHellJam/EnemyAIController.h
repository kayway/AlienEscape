// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"

#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class BULLETHELLJAM_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:

	AEnemyAIController(FObjectInitializer const& object_initializer = FObjectInitializer::Get());
	void OnPossess(APawn* const pawn) override;

	AActor* GetTargetPawn();
private:
	UPROPERTY()
		UBlackboardComponent* BlackboardComponent;
};
