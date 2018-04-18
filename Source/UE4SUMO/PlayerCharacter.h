// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//Engine specific headers
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GenericTeamAgentInterface.h"

//Required headers
#include "GameFramework/Character.h"
#include "CoreMinimal.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class UE4SUMO_API APlayerCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float MoveAmount);

    void MoveRight(float MoveAmount);

	void Run(float RunSpeed);

	void Dash();

	void Punch();

	void EatUnhealthy(float SizeIncrease);

	void EatHealthy(float SizeDecrease);

	UPROPERTY(EditAnywhere)
	float Speed = 300.f;

	FVector CurrentLocation;

	UPROPERTY(EditDefaultsOnly, Category = Curve)
	UCurveFloat* Curve;

	float Size = 1.0f;

	bool bRunning = false;

	FGenericTeamId TeamId;

	virtual FGenericTeamId GetGenericTeamId() const override;

	float PlayerSize = 60.f;

private:
	UPROPERTY(EditAnywhere)
	FTransform CameraTransform;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera = nullptr;

	float RotationValue = -90.f;

	float FrameTime = 0.f;

	FRotator LungeDirection;
};
