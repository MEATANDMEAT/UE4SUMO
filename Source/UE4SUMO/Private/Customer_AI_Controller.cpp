// Fill out your copyright notice in the Description page of Project Settings.

#include "Customer_AI_Controller.h"

ACustomer_AI_Controller::ACustomer_AI_Controller()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACustomer_AI_Controller::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.TickInterval = 3.f;
}

void ACustomer_AI_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	if ((GetPawn()->GetActorLocation() - Result.Location).Size() < 10.f)
	{
		bRandomPointGenerated = false;
		bMoveToIsRunning = false;
	}
}

void ACustomer_AI_Controller::GetRandomPoint()
{
	Result.Location = UNavigationSystem::GetCurrent(GetWorld())->GetRandomReachablePointInRadius(GetWorld(), GetPawn()->GetActorLocation(), 500);
	Result.Location.Z = GetPawn()->GetActorLocation().Z;
}

void ACustomer_AI_Controller::MoveToRandomPoint()
{
	MoveToLocation(Result.Location, 5.f, false, true, true, true, 0, true);
}
