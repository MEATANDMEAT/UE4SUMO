// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PlayerCharacter.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Employees_AI_Controller.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

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

	UFUNCTION()
		void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
		void OnNoiseHear(APawn* NoiseInstigator, const FVector& Location, float Volume);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnPlayerOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditAnywhere, Category = AI)
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, Category = AI)
		class UPawnSensingComponent* PawnSensingComp;


private:

};
