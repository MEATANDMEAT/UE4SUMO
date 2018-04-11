// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//Custom headers
#include "EnemyCharacter.h"
#include "PlayerCharacter.h"

//Engine specific headers
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AI/Navigation/NavigationSystem.h"

//Required headers
#include "CoreMinimal.h"
#include "AIController.h"
#include "Employees_AI_Controller.generated.h"

class AEnemyCharacter;
class APlayerCharacter;
UCLASS()
class UE4SUMO_API AEmployees_AI_Controller : public AAIController
{
	GENERATED_BODY()

	UBlackboardComponent* BlackboardComp;
	UBehaviorTreeComponent* BehaviorComp;


	virtual void Possess(APawn* Pawn) override;

public:
	// Sets default values for this actor's properties
	AEmployees_AI_Controller();

	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*> &Actors);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI Perception")
		float AISightRadius = 700.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI Perception")
		float AISightAge = 5.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI Perception")
		float AILoseSightRadius = AISightRadius + 50.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI Perception")
		float AISightAngle = 90.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI Perception")
		class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI Perception")
		bool bIsPlayerDetected = false;

	UPROPERTY(EditDefaultsOnly, Category = AI)
		FName RandomLocationKey;

	FTimerHandle TimerHandle;

	bool bBehaviorTreeRunning = false;

	FVector LastSeenLocation;

	bool bAIRemember = false;

	FNavLocation Result;

	bool bRandomPointGenerated = false;

	void GetRandomPoint();

	void MoveToRandomPoint();

	bool bMoveToIsRunning = false;

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

protected:
	// Called when the game starts or when the actor is spawned in the world
		void BeginPlay() override;


public:
	// Is called every frame when the actor is present in the world
	   void Tick(float DeltaTime) override;
	
};
