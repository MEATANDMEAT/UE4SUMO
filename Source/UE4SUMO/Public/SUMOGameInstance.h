// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SUMOGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE4SUMO_API USUMOGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	USUMOGameInstance(const FObjectInitializer& ObjectInitializer);

	/** Store Player's lives and total score here! */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = GameVariables)
		uint8 PlayerLives = 4;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = GameVariables)
		float TotalPlayerScore;


	
};
