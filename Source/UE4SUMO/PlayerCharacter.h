// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//Engine specific headers
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/TextRenderActor.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Components/BillboardComponent.h"

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

	void ChangeValues(float Value);

	void RunCooldown();

	void Caught();

	void Respawn();

	void Countdown();

	virtual FGenericTeamId GetGenericTeamId() const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	uint8 Lives = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBillboardComponent* RageSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bShowGameOver = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bShowRoundEnd = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bNotEnoughScoreText = false;

	UPROPERTY(EditAnywhere)
	float Speed = 360.f;

	UPROPERTY(EditAnywhere)
	float SizeMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDestroyedByEnemy = false;

	UPROPERTY(EditAnywhere)
	float SpeedMultiplier = 90.f;

	UPROPERTY(EditAnywhere)
	float ScoreMultiplier = 50000.f;

	UPROPERTY(EditAnywhere)
	float DashValue = 37.f;

	UPROPERTY(EditDefaultsOnly, Category = Curve)
	UCurveFloat* DashCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Stamina = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Score = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float DashCooldown = 3.f;

	UPROPERTY(BlueprintReadWrite)
	float DashCooldownAlpha = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TimerSeconds = 120;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int TimerMinutes = 0;

	UPROPERTY(EditAnywhere)
	UAnimationAsset* DefaultAnimations;

	UPROPERTY(EditAnywhere)
	UAnimationAsset* KnockedOutAnimation;

	FNavLocation Result;

	bool bPlayerRage = false;

	float Size = 1.0f;

	bool bRunning = false;

	FGenericTeamId TeamId;

	bool bSpeedPickup = false;

	bool bChiliPickup = false;

	float PrevSpeed = 0.f;

	bool bDashing = false;

	bool bKnockedOut = false;

	FTimerHandle RespawnTimer;

	FTimerHandle CaughtTimer;

	FTimerHandle LevelTimerHandle;

private:
	UPROPERTY(EditAnywhere)
	FTransform CameraTransform;

	UMaterialInstanceDynamic* DynMats[10];

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera = nullptr;

	float RotationValue = -90.f;

	float FrameTime = 0.f;

	float DashAlpha = 0.f;

	bool bEnableInput = true;

	FRotator LungeDirection;

	bool bRegainStamina = true;

	FTimerHandle RunTimer;

	unsigned int RunFatigue = 2;

	uint8 CaughtCooldown = 5;

	uint8 RespawnCooldown = 8;

	bool bCanDash = true;

	FVector TEMP;

	FVector NewTEMP;

};
