// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Employees_AI_Controller.h"
#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTConeCheck_Service.generated.h"

/**
 * 
 */
UCLASS()
class UE4SUMO_API UBTConeCheck_Service : public UBTService
{
	GENERATED_BODY()
		UBTConeCheck_Service(const FObjectInitializer& ObjectInitializer);
		
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	FVector PlayerLocation;
	FVector EnemyLocation;
	FVector PlayerToEnemyLine;
	FVector NULL_LOCATION;
	float DotProduct;
	float Radian;
	float Angle;
};
