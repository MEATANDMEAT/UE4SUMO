// Fill out your copyright notice in the Description page of Project Settings.

#include "Employees_AI_Controller.h"

// Sets default values
AEmployees_AI_Controller::AEmployees_AI_Controller()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	RandomLocationKey = "RandomLocation";

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AI Perception Component");

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AISightAngle;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;

	PerceptionComponent->SetDominantSense(*SightConfig->GetSenseImplementation());
	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEmployees_AI_Controller::OnPerceptionUpdated);
	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->bEditableWhenInherited = true;
}

FRotator AEmployees_AI_Controller::GetControlRotation() const
{
	if (GetPawn() == nullptr)
	{
		return FRotator(0.f, 0.f, 0.f);
	}
	return FRotator(0.f, GetPawn()->GetActorRotation().Yaw, 0.f);
}

void AEmployees_AI_Controller::OnPerceptionUpdated(const TArray<AActor*>& Actors)
{
	auto Player = Actors.FindByKey(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (bIsPlayerDetected == false && Player)
	{
		bIsPlayerDetected = true;
		UE_LOG(LogTemp, Warning, TEXT("bPlayerDetected %i"), bIsPlayerDetected);
	}
	else if (bIsPlayerDetected && Player)
	{
		bIsPlayerDetected = false;
		UE_LOG(LogTemp, Warning, TEXT("bPlayerDetected %i"), bIsPlayerDetected);
	}
}

void AEmployees_AI_Controller::Possess(APawn * Pawn)
{
	Super::Possess(Pawn);
	//AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(Pawn);
//	if (EnemyCharacter)
//	{
//		if (EnemyCharacter->BehaviorTree->BlackboardAsset)
//		{
//			BlackboardComp->InitializeBlackboard(*(EnemyCharacter->BehaviorTree->BlackboardAsset));
//	  }
//		BehaviorComp->StartTree(*EnemyCharacter->BehaviorTree);
//	}
}


void AEmployees_AI_Controller::GetRandomPoint()
{
	UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(GetWorld());
	Result.Location = NavSys->GetRandomReachablePointInRadius(GetWorld(), GetPawn()->GetActorLocation(), 2000.f);
	//	/*Result.Location = NavSys->GetRandomPointInNavigableRadius(
	//		GetWorld(),
	//		GetPawn()->GetActorLocation(),
	//		2000.f);*/
	Result.Location += FVector(0.f, 0.f, 87.275f);
	UE_LOG(LogTemp, Warning, TEXT("Result Location is: %s"), *(Result.Location.ToString()))
	RandomPointGenerated = false;
}

void AEmployees_AI_Controller::MoveToRandomPoint()
{
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
	MoveToLocation(Result.Location, 5.f, false, true, true, true, 0, true);
	if ((EnemyCharacter->GetActorLocation() - Result.Location).Size() < 10.f)
	{
		RandomPointGenerated = false;
		MoveToRunning = false;
	}
}

// Called when the game starts or when spawned
void AEmployees_AI_Controller::BeginPlay()
{
	Super::BeginPlay();
	AEnemyCharacter* GetControlledEnemy = Cast<AEnemyCharacter>(GetPawn());
	UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(GetWorld());
	Result.Location = NavSys->GetRandomReachablePointInRadius(GetWorld(), GetPawn()->GetActorLocation(), 2000.f);
   
}

// Called every frame
void AEmployees_AI_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PrimaryActorTick.TickInterval = 0.1f;
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(GetWorld());


	if (bIsPlayerDetected && PlayerCharacter)
	{
		MoveToActor(PlayerCharacter, 0.f,false,true,true,0,false);
		LastSeenLocation = PlayerCharacter->GetActorLocation();
		bAIRemember = true;
	}

	else if (bIsPlayerDetected == false && PlayerCharacter && bAIRemember)
	{
		if ((EnemyCharacter->GetActorLocation() - LastSeenLocation).Size() < 10.f)
		{
			bAIRemember = false;
		}
		else if ((EnemyCharacter->GetActorLocation() - LastSeenLocation).Size() > 10.f)
		{
			MoveToLocation(LastSeenLocation, 5.f,false,true,false,true,0,false);
		}
	}

	else if (bIsPlayerDetected == false && PlayerCharacter && bAIRemember == false)
	{
		if (RandomPointGenerated == false && MoveToRunning == false)
		{
			GetRandomPoint();
			RandomPointGenerated = true;
		}
		else if (RandomPointGenerated && MoveToRunning == false)
		{
			MoveToRandomPoint();
			MoveToRunning = true;
		}
	}
}

