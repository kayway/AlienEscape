// Fill out your copyright notice in the Description page of Project Settings.


#include "FindTargetQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BulletHellJamPawn.h"
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"

void UFindTargetQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	//Get the Owner of this Query and cast it to an actor
	//Then, get the actor's controller and cast to it our AIController
	//This code works for our case but avoid that many casts and one-liners in cpp.
	AEnemyAIController* AICont = Cast<AEnemyAIController>((Cast<AActor>((QueryInstance.Owner).Get())->GetInstigatorController()));

	if (AICont && AICont->GetTargetPawn())
	{
		//BlackboardComponent->GetValueAsObject(blackboardkeys::Target)
		//Set the context SeeingPawn to the provided context data
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, AICont->GetTargetPawn());
	}
	//Set the context SeeingPawn to the provided context data
	//UEnvQueryItemType_Actor::SetContextHelper(ContextData, FoundActors[0]);
}