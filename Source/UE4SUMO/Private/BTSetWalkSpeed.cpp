// Fill out your copyright notice in the Description page of Project Settings.

#include "BTSetWalkSpeed.h"
#include "EnemyCharacter.h"
#include "Employees_AI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTSetWalkSpeed::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AEmployees_AI_Controller* AIController = Cast<AEmployees_AI_Controller>(OwnerComp.GetAIOwner());
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(AIController->GetPawn());

	if (AIController)
	{
		EnemyCharacter->GetCharacterMovement()->MaxWalkSpeed = 300.f;

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
