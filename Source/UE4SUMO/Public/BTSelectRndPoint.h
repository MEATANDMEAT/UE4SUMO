// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//Required headers
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTSelectRndPoint.generated.h"

/**
 * 
 */
UCLASS()
class UE4SUMO_API UBTSelectRndPoint : public UBTTaskNode
{
	GENERATED_BODY()

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
		
	
};
