// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//Custom headers
#include "PlayerCharacter.h"
#include "Employees_AI_Controller.h"

//Engine specific headers
#include "BehaviorTree/BehaviorTree.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

//Required headers
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class UE4SUMO_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPlayerOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditAnywhere, Category = AI)
		class UBehaviorTree* BehaviorTree;


private:

};
