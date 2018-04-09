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

void AEmployees_AI_Controller::GetNewPlayerLocation()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	NewPlayerLocation = PlayerCharacter->GetActorLocation();

}

// Called when the game starts or when spawned
void AEmployees_AI_Controller::BeginPlay()
{
	Super::BeginPlay();
	AEnemyCharacter* GetControlledEnemy = Cast<AEnemyCharacter>(GetPawn());
	UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(GetWorld());
	if (GetControlledEnemy != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("C++ controller has now possesed: %s"), (*GetControlledEnemy->GetName()))
	} else UE_LOG(LogTemp, Warning, TEXT("C++ controller has not possesed anything!"), (*GetControlledEnemy->GetName()))
	
	Result.Location = NavSys->GetRandomReachablePointInRadius(GetWorld(), GetPawn()->GetActorLocation(), 2000.f);
   
}

// Called every frame
void AEmployees_AI_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PrimaryActorTick.TickInterval = 0.1f;
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	USkeletalMeshComponent *SkelMesh = EnemyCharacter->FindComponentByClass<USkeletalMeshComponent>();
	UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(GetWorld());


	if (bIsPlayerDetected && PlayerCharacter && SkelMesh)
	{
		MoveToActor(PlayerCharacter, 0.f,false,true,true,0,false);
		LastSeenLocation = PlayerCharacter->GetActorLocation();
		SkelMesh->PlayAnimation(Running, true);
		bAIRemember = true;
	}

	else if (bIsPlayerDetected == false && PlayerCharacter && SkelMesh && bAIRemember)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEmployees_AI_Controller::GetNewPlayerLocation, 1.f, false, 0.f);

		if (EnemyCharacter->GetActorLocation().Equals(LastSeenLocation,5.f))
		{
			bAIRemember = false;
			UE_LOG(LogTemp, Warning, TEXT("EnemyLocation equals LastSeenLocation, 5 tolerance"));
		}
		else if (EnemyCharacter->GetActorLocation().Equals(LastSeenLocation,5.f) == false)
		{
			MoveToLocation(LastSeenLocation, 0.f,false,true,false,true,0,false);
			UE_LOG(LogTemp, Warning, TEXT("EnemyLocation does not equal LastSeenLocation, 5 tolerance"), (EnemyCharacter->GetActorLocation() - LastSeenLocation).Size());
		}
	}

	else if (bIsPlayerDetected == false && PlayerCharacter && SkelMesh && bAIRemember == false)
	{
		if (EnemyCharacter->GetActorLocation().Equals(LastSeenLocation,5.f))
		{
			Result.Location = NavSys->GetRandomReachablePointInRadius(GetWorld(), GetPawn()->GetActorLocation(), 2000.f);
			/*Result.Location = NavSys->GetRandomPointInNavigableRadius(
				GetWorld(),
				GetPawn()->GetActorLocation(),
				2000.f);*/
			MoveToLocation((Result.Location), 0.f, false, true, true, true, 0, true);
			UE_LOG(LogTemp, Warning, TEXT("Random point is at %s"), *(Result.Location.ToString()))
		}
		else if (EnemyCharacter->GetActorLocation().Equals(Result.Location, 0.f) == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("Distance to random point: %f"), (EnemyCharacter->GetActorLocation() - Result.Location).Size())
			MoveToLocation((Result.Location), 0.f,false,true,true,true,0,true);
		}
	}
}

