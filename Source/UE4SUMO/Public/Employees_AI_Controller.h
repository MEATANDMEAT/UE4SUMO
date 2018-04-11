// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "EnemyCharacter.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/PawnSensingComponent.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationSystem.h"
#include "Employees_AI_Controller.generated.h"


UCLASS()
class UE4SUMO_API AEmployees_AI_Controller : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEmployees_AI_Controller();

	FNavLocation Result;
	UNavigationSystem* NavSys;
	unsigned char AIState;
	FVector Target;
	UPROPERTY(VisibleAnywhere, Category = AI)
	class UPawnSensingComponent* PawnSensingComp;

protected:
	// Called when the game starts or when the actor is spawned in the world
	void BeginPlay() override;
	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

public:
	// Is called every frame when the actor is present in the world
	   void Tick(float DeltaTime) override;
	
};
