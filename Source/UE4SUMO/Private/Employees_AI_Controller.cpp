// Fill out your copyright notice in the Description page of Project Settings.

#include "Employees_AI_Controller.h"


void AEmployees_AI_Controller::Possess(APawn * Pawn)
{
	Super::Possess(Pawn);
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(Pawn);
	if (EnemyCharacter)
	{
		if (EnemyCharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(EnemyCharacter->BehaviorTree->BlackboardAsset));
	  }
		BehaviorComp->StartTree(*EnemyCharacter->BehaviorTree);
	}
}

// Sets default values
AEmployees_AI_Controller::AEmployees_AI_Controller()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	RandomLocationKey = FVector(0.f,0.f,0.f);
	PlayerKey = "Target";
}

void AEmployees_AI_Controller::SetPlayerSeen(APawn * Pawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(PlayerKey, Pawn);
	}
}

// Called when the game starts or when spawned
void AEmployees_AI_Controller::BeginPlay()
{
	Super::BeginPlay();
	AEnemyCharacter* GetControlledEnemy = Cast<AEnemyCharacter>(GetPawn());
	if (GetControlledEnemy != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("C++ controller has now possesed: %s"), (*GetControlledEnemy->GetName()))
	} else UE_LOG(LogTemp, Warning, TEXT("C++ controller has not possesed anything!"), (*GetControlledEnemy->GetName()))
   
}

// Called every frame
void AEmployees_AI_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

