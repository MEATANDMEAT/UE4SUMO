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

	void DashCooldown();

	void RunCooldown();

	UPROPERTY(EditAnywhere)
	float Speed = 300.f;

	UPROPERTY(EditAnywhere)
	float DashValue = 50.f;

	FVector CurrentLocation;

	UPROPERTY(EditDefaultsOnly, Category = Curve)
	UCurveFloat* Curve;

	UPROPERTY(EditDefaultsOnly, Category = Curve)
	UCurveFloat* DashCurve;
	
	float Size = 1.0f;

	bool bRunning = false;

	FGenericTeamId TeamId;

	virtual FGenericTeamId GetGenericTeamId() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerSize = 60.f;

	bool bSpeedPickup = false;

	bool bChiliPickup = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Stamina = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Score;

private:
	UPROPERTY(EditAnywhere)
	FTransform CameraTransform;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera = nullptr;

	float RotationValue = -90.f;

	float FrameTime = 0.f;

	float DashAlpha = 0.f;

	bool bDashing = false;

	bool bEnableInput = true;

	float PrevSpeed = 0.f;

	FRotator LungeDirection;

	bool bCooldown = false;

	bool bRegainStamina = true;

	FTimerHandle Timer;

	FTimerHandle RunTimer;

	unsigned int CheckCooldownTimer = 6;

	unsigned int CheckRunCooldownTimer = 2;
};
