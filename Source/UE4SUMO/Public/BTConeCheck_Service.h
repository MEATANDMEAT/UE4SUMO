// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//Custom headers
#include "Employees_AI_Controller.h"

//Required headers
#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTConeCheck_Service.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAI_State : uint8 //must be uint8 for UENUM(BlueprintType) to work
{
	AI_FindPlayer UMETA(DisplayName = "Find Player"),
	AI_ChasePlayer UMETA(DisplayName = "Chase Player"),
	AI_PlayerLastSeen UMETA(DisplayName = "Last Seen Player Location")
};


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
	float DotProduct;
	float Radian;
	float Angle;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBlackboardKeySelector AI_State_BBKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBlackboardKeySelector LastSeenLocation;

	FVector LastSeenLocation_VECTOR;

	FVector LastSeenDistance;

	bool AIRemember;

	//Target (PlayerCharacter)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector Target;



};
