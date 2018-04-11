// Fill out your copyright notice in the Description page of Project Settings.

#include "BTSelectRndPoint.h"
#include "Employees_AI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationSystem.h"

EBTNodeResult::Type UBTSelectRndPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AEmployees_AI_Controller* AIController = Cast<AEmployees_AI_Controller>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComp();
		UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(GetWorld());
		if (!NavSys)
		{
			UE_LOG(LogTemp, Warning, TEXT("Could not get NAV System"))
		}

		FNavLocation Result;
		//Result.Location = NavSys->GetRandomReachablePointInRadius(GetWorld(), AIController->GetPawn()->GetActorLocation(), 3000.f);
		Result.Location = NavSys->GetRandomPointInNavigableRadius(
			GetWorld(),
			AIController->GetPawn()->GetActorLocation(),
			2000.f);

		if (Result.Location == FVector(0.f,0.f,0.f))
		{
			UE_LOG(LogTemp, Warning, TEXT("Could not get a random point"))
		}
			//Success
		UE_LOG(LogTemp, Warning, TEXT("Random point is at %s"), *(Result.Location.ToString()))
		BlackboardComp->SetValueAsVector(AIController->RandomLocationKey, Result.Location);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}