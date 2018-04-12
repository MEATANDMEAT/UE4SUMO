// Fill out your copyright notice in the Description page of Project Settings.

#include "Customer_AI_Controller.h"

ACustomer_AI_Controller::ACustomer_AI_Controller()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACustomer_AI_Controller::BeginPlay()
{
	PrimaryActorTick.TickInterval = 0.2f;
}

void ACustomer_AI_Controller::Tick(float DeltaTime)
{
	if (bRandomPointGenerated == false && bMoveToIsRunning == false)
	{
		GetRandomPoint();
		//Set bRandomPointGenerated to true, in order to stop the tick from running the same task again.
		bRandomPointGenerated = true;
		UE_LOG(LogTemp,Warning,TEXT("Stuck in RPointGen = false, MoveTo= false"))
	}
	//Then check if we have generated a random point and that the AI is in idle.
	if (bRandomPointGenerated && bMoveToIsRunning == false)
	{
		MoveToRandomPoint();
		//Set bMoveToIsRunning to true, in order to stop the tick from running the same task again.
		bMoveToIsRunning = true;
		UE_LOG(LogTemp, Warning, TEXT("Stuck in RPointGen = true, MoveTo= false"))
	}
	//Check if the AI is near the random point, when it is, set the AI to idle and generate a random point again.
	//Repeat the whole process again.
	if ((GetPawn()->GetActorLocation() - Result.Location).Size() < 10.f)
	{
		bRandomPointGenerated = false;
		bMoveToIsRunning = false;
		UE_LOG(LogTemp, Warning, TEXT("RPoint less than 10"))
	}
	UE_LOG(LogTemp, Warning, TEXT("Tick is running"))
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
