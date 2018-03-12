// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "EnemyCharacter.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "Employees_AI_Controller.generated.h"

/**
 * 
 */
UCLASS()
class UE4SUMO_API AEmployees_AI_Controller : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEmployees_AI_Controller();

protected:
	// Called when the game starts or when the actor is spawned in the world
		void BeginPlay() override;

public:
	// Is called every frame when the actor is present in the world
	   void Tick(float DeltaTime) override;
	
};
