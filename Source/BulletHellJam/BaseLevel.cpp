// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevel.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


/*void ABaseLevel::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ABulletHellJamPawn::StaticClass(), FName("Player"), Players);
}
FVector ABaseLevel::GetPlayerLocation()
{
	FVector Location;
	for (size_t i = 0; i < Players.Num(); ++i)
	{
		Location = Players[i]->GetActorLocation();
	}
	return Location;
}*/