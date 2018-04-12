// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


//Engine specific headers
#include "AI/Navigation/NavigationSystem.h"

//Requried headers
#include "CoreMinimal.h"
#include "AIController.h"
#include "Customer_AI_Controller.generated.h"

/**
 * 
 */
UCLASS()
class UE4SUMO_API ACustomer_AI_Controller : public AAIController
{
	GENERATED_BODY()

		ACustomer_AI_Controller();
public:
		void BeginPlay() override;

	    void Tick(float DeltaTime) override;

		FNavLocation Result;

		bool bRandomPointGenerated = false;

		void GetRandomPoint();

		void MoveToRandomPoint();

		bool bMoveToIsRunning = false;
private:
	
	
};
