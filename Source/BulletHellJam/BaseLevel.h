// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "BulletHellJamPawn.h"

#include "BaseLevel.generated.h"

/**
 * 
 */
UCLASS()
class BULLETHELLJAM_API ABaseLevel : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	/*virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	UPROPERTY(Category = Gameplay, VisibleAnywhere, BlueprintReadOnly)
		TArray<AActor*> Players;
	FVector GetPlayerLocation();*/
};
