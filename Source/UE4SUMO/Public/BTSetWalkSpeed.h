// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTSetWalkSpeed.generated.h"

/**
 * 
 */
UCLASS()
class UE4SUMO_API UBTSetWalkSpeed : public UBTTaskNode
{
	GENERATED_BODY()
	
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkSpeed;
	
};
