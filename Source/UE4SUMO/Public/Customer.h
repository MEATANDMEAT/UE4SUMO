// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//Custom headers
#include "PlayerCharacter.h"

//Engine specific headers
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"

//Required headers
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Customer.generated.h"

UCLASS()
class UE4SUMO_API ACustomer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACustomer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OnPlayerOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	
};
