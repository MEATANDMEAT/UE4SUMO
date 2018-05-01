// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//Customer headers
#include "PlayerCharacter.h"

//Engine headers
#include "Components/BillboardComponent.h"

//Required headers
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreSplash.generated.h"

UCLASS()
class UE4SUMO_API AScoreSplash : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScoreSplash();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	USceneComponent* FoodRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBillboardComponent* Score;

private:
	void OnTimerEnd();

	FTimerHandle Timer;

	uint8 Seconds = 3;

	
};
