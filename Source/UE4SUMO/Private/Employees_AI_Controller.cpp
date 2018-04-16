// Fill out your copyright notice in the Description page of Project Settings.

#include "Employees_AI_Controller.h"

// Sets default values
AEmployees_AI_Controller::AEmployees_AI_Controller()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	{
		SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
		PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AI Perception Component");

		SightConfig->SightRadius = AISightRadius;
		SightConfig->LoseSightRadius = AILoseSightRadius;
		SightConfig->PeripheralVisionAngleDegrees = AISightAngle;
		SightConfig->SetMaxAge(AISightAge);

		SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = false;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;

		PerceptionComponent->SetDominantSense(*SightConfig->GetSenseImplementation());
		PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEmployees_AI_Controller::OnPerceptionUpdated);
		PerceptionComponent->ConfigureSense(*SightConfig);
		PerceptionComponent->bEditableWhenInherited = true;

		SetGenericTeamId(FGenericTeamId(0));
	}
}

void AEmployees_AI_Controller::OnPerceptionUpdated(const TArray<AActor*>& Actors)
{
	//Set bIsPlayerDetected to true when the AI's perception updates and vice versa.
	//This will switch between true and false each time the percetion is updated.
	if (bIsPlayerDetected == false)
	{
		bIsPlayerDetected = true;
	}
	else if (bIsPlayerDetected)
	{
		bIsPlayerDetected = false;
	}
}
void AEmployees_AI_Controller::Possess(APawn * Pawn)
{
	Super::Possess(Pawn);
}

/*Generates a random location in the navigable mesh that the AI can reach and stores it inside Result.*/
void AEmployees_AI_Controller::GetRandomPoint()
{
	UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(GetWorld());
	Result.Location = NavSys->GetRandomReachablePointInRadius(GetWorld(), GetPawn()->GetActorLocation(), 1500.f);
	Result.Location.Z = GetPawn()->GetActorLocation().Z;
}

/*Move the AI to the location stored inside Result
NOTE: Result must be assigned to a valid location, use GetRandomReachablePointInRadius.*/
void AEmployees_AI_Controller::MoveToRandomPoint()
{
	MoveToLocation(Result.Location, 5.f, false, true, true, true, 0, true);
}

void AEmployees_AI_Controller::BeginPlay()
{
	Super::BeginPlay();
	EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
	PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void AEmployees_AI_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//When the player is detected and the pointer to player isn't NULL, move the AI
	//to Player's current position. We use a vector(LastSeenLocation) to store player's position
	//in order to give the AI memory.
	if (bIsPlayerDetected && PlayerCharacter)
	{
		MoveToActor(PlayerCharacter, 0.f, false, true, true, 0, false);
		LastSeenLocation = PlayerCharacter->GetActorLocation();
		//Set AIRemember to true, so it has to move to LastSeenLocation.
		bAIRemember = true;
	}
	//After the AI loses sight of the player, it moves to the LastSeenLocation vector.
	//Which is the last position the AI recorded of Player's position.
	else if (bIsPlayerDetected == false && PlayerCharacter && bAIRemember)
	{
		if ((EnemyCharacter->GetActorLocation() - LastSeenLocation).Size() < 5.f)
		{
			//After the AI loses sight of the player, and is near LastSeenLocation
			//assign the random point to player's new position.
			//This is to give the illusion that the AI predicted where the player could have moved, instead
			//of the AI just turning around 180 degrees after it moves to the last seen position of the player
			Result.Location = PlayerCharacter->GetActorLocation();
			bAIRemember = false;
			bRandomPointGenerated = true;
			bMoveToIsRunning = false;
		}
		//If the AI isn't close the last seen position of the player, then move until it is.
		else if ((EnemyCharacter->GetActorLocation() - LastSeenLocation).Size() > 5.f)
		{
			MoveToLocation(LastSeenLocation, 1.f, false, true, false, true, 0, false);
		}
	}
	//When the player has not been detected and the AI does not remember any last positions of the player.
	else if (bIsPlayerDetected == false && PlayerCharacter && bAIRemember == false)
	{
		//Check if the random point has not already been generated and that the AI is in idle.
		if (bRandomPointGenerated == false && bMoveToIsRunning == false)
		{
			GetRandomPoint();
			//Set bRandomPointGenerated to true, in order to stop the tick from running the same task again.
			bRandomPointGenerated = true;
		}
		//Then check if we have generated a random point and that the AI is in idle.
		if (bRandomPointGenerated && bMoveToIsRunning == false)
		{
			MoveToRandomPoint();
			//Set bMoveToIsRunning to true, in order to stop the tick from running the same task again.
			bMoveToIsRunning = true;
		}
		//Check if the AI is near the random point, when it is, set the AI to idle and generate a random point again.
		//Repeat the whole process again.
		if ((EnemyCharacter->GetActorLocation() - Result.Location).Size() < 10.f)
		{
			bRandomPointGenerated = false;
			bMoveToIsRunning = false;
		}
	}
}

