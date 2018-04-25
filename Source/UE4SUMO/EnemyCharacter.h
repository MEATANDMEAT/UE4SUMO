// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//Custom headers
#include "PlayerCharacter.h"
#include "Employees_AI_Controller.h"

//Engine specific headers
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BillboardComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

//Required headers
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBillboardComponent* Exclaimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBillboardComponent* Question;

	FTimerHandle RageTimer;

	void OnPlayerRage();

	int FunctionRepeats = 0;

	float FallRotation;
private:


};
