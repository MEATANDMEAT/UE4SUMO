// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "components/SkeletalMeshComponent.h"
#include "PlayerCharacter.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UPawnSensingComponent;
UENUM(BlueprintType)
enum class EAIState : uint8 //must be uint8 for UENUM(BlueprintType) to work
{
	Patrolling UMETA(DisplayName = "Patrolling"),
	Suspicous UMETA(DisplayName = "Suspicious"),
	Alerted UMETA(DisplayName = "Alerted"),
	LastSeen UMETA(DisplayName = "LastSeen")
};

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

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
		void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
		void OnNoiseHear(APawn* NoiseInstigator, const FVector& Location, float Volume);

	EAIState EnemyState;

	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
		void OnStateChanged(EAIState NewState);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnPlayerOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

private:
};
