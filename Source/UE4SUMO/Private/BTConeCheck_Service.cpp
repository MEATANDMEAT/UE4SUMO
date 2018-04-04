// Fill out your copyright notice in the Description page of Project Settings.

#include "BTConeCheck_Service.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"

UBTConeCheck_Service::UBTConeCheck_Service(const FObjectInitializer & ObjectInitializer)
{
	NodeName = "Cone Check Pawn";
}

void UBTConeCheck_Service::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	///Initializing all the nessecarry pointers we will be using later
	AEmployees_AI_Controller* AIController = Cast<AEmployees_AI_Controller>(OwnerComp.GetAIOwner());
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(AIController->GetPawn());
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComp();

	//Set up an empty vector to compare later
	NULL_LOCATION = FVector(0.f, 0.f, 0.f);

	//Check to see if AIController, PlayerCharacter and EnemyCharacter return a valid pointer value
	if (AIController && PlayerCharacter && EnemyCharacter)
	{			
		//Get a vector line between player
		PlayerLocation = PlayerCharacter->GetActorLocation();
		EnemyLocation = EnemyCharacter->GetActorLocation();
		PlayerToEnemyLine = PlayerLocation - EnemyLocation;

		//Normalize vector in order to calculate the angle later
		PlayerToEnemyLine.Normalize();

		//Calculate the dotproduct and the angle between enemy forward vector and the line from player to enemy
		DotProduct = FVector::DotProduct(PlayerToEnemyLine, EnemyCharacter->GetActorForwardVector());
		Radian = FMath::Acos(DotProduct);
		Angle = FMath::RadiansToDegrees(Radian);

		  //Set a limit to the angle, in order to give the enemy a reasonable sight radius
		  if (Angle < 80.f)
		  {
		  	  UE_LOG(LogTemp, Warning, TEXT("Player in angle"))
		  }
		  else UE_LOG(LogTemp, Warning, TEXT("Player now out of angle"))
		
	  ///TODO: Ray cast to see what the line hits, if player then set AI_State to Chase target, if not set AI_State to FindPlayer
	  ///When done, clean up PawnSensingComponent (Or maybe use later for OnHearNoise event?)
	}
}
